find_vfs_mount (const char *dbus_id,
		const char *obj_path)
{
  GList *l;
  for (l = mounts; l != NULL; l = l->next)
    {
      VfsMount *mount = l->data;

      if (strcmp (mount->dbus_id, dbus_id) == 0 &&
	  strcmp (mount->object_path, obj_path) == 0)
	return mount;
    }

  return NULL;
}
