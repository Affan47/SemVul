update_fstab_volumes (GVfsUDisks2VolumeMonitor  *monitor,
                      GList                    **added_volumes,
                      GList                    **removed_volumes,
                      gboolean                   coldplug)
{
  GList *cur_mount_points;
  GList *new_mount_points;
  GList *added;
  GList *removed;
  GList *l, *ll;
  GVfsUDisks2Volume *volume;

  cur_mount_points = NULL;
  for (l = monitor->fstab_volumes; l != NULL; l = l->next)
    {
      GUnixMountPoint *mount_point = gvfs_udisks2_volume_get_mount_point (GVFS_UDISKS2_VOLUME (l->data));
      if (mount_point != NULL)
        cur_mount_points = g_list_prepend (cur_mount_points, mount_point);
    }

  new_mount_points = g_unix_mount_points_get (NULL);

  for (l = new_mount_points; l != NULL; l = ll)
    {
      GUnixMountPoint *mount_point = l->data;

      ll = l->next;

      if (!should_include_mount_point (monitor, mount_point) ||
          have_udisks_volume_for_mount_point (monitor, mount_point) ||
          !mount_point_has_device (monitor, mount_point))
        {
          new_mount_points = g_list_remove_link (new_mount_points, l);
          g_unix_mount_point_free (mount_point);
        }
    }

  cur_mount_points = g_list_sort (cur_mount_points, (GCompareFunc) g_unix_mount_point_compare);
  new_mount_points = g_list_sort (new_mount_points, (GCompareFunc) g_unix_mount_point_compare);
  diff_sorted_lists (cur_mount_points,
                     new_mount_points, (GCompareFunc) g_unix_mount_point_compare,
                     &added, &removed, NULL);

  for (l = removed; l != NULL; l = l->next)
    {
      GUnixMountPoint *mount_point = l->data;
      volume = find_fstab_volume_for_mount_point (monitor, mount_point);
      if (volume != NULL)
        {
          gvfs_udisks2_volume_removed (volume);
          monitor->fstab_volumes = g_list_remove (monitor->fstab_volumes, volume);
          *removed_volumes = g_list_prepend (*removed_volumes, g_object_ref (volume));
          g_object_unref (volume);
        }
    }

  for (l = added; l != NULL; l = l->next)
    {
      GUnixMountPoint *mount_point = l->data;

      volume = find_fstab_volume_for_mount_point (monitor, mount_point);
      if (volume != NULL)
        continue;

      volume = gvfs_udisks2_volume_new (monitor,
                                        NULL,
                                        mount_point,
                                        NULL,
                                        NULL,
                                        coldplug);
      if (volume != NULL)
        {
          GVfsUDisks2Mount *mount;

          monitor->fstab_volumes = g_list_prepend (monitor->fstab_volumes, volume);
          *added_volumes = g_list_prepend (*added_volumes, g_object_ref (volume));

          new_mount_points = g_list_remove (new_mount_points, mount_point);


          mount = find_lonely_mount_for_mount_point (monitor, mount_point);
          if (mount != NULL)
            gvfs_udisks2_mount_set_volume (mount, volume);
        }
    }

  g_list_free_full (new_mount_points, (GDestroyNotify) g_unix_mount_point_free);

  g_list_free (cur_mount_points);
}
