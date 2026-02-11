get_disk (char const *disk)
{
  struct mount_entry const *me;
  struct mount_entry const *best_match = NULL;
  bool best_match_accessible = false;
  bool eclipsed_device = false;
  char const *file = disk;

  char *resolved = canonicalize_file_name (disk);
  if (resolved && IS_ABSOLUTE_FILE_NAME (resolved))
    disk = resolved;

  size_t best_match_len = SIZE_MAX;
  for (me = mount_list; me; me = me->me_next)
    {

      char *devname = me->me_devname;
      char *canon_dev = canonicalize_file_name (me->me_devname);
      if (canon_dev && IS_ABSOLUTE_FILE_NAME (canon_dev))
        devname = canon_dev;

      if (STREQ (disk, devname))
        {
          char *last_device = last_device_for_mount (me->me_mountdir);
          eclipsed_device = last_device && ! STREQ (last_device, devname);
          size_t len = strlen (me->me_mountdir);

          if (! eclipsed_device
              && (! best_match_accessible || len < best_match_len))
            {
              struct stat disk_stats;
              bool this_match_accessible = false;

              if (stat (me->me_mountdir, &disk_stats) == 0)
                best_match_accessible = this_match_accessible = true;

              if (this_match_accessible
                  || (! best_match_accessible && len < best_match_len))
                {
                  best_match = me;
                  if (len == 1)
                    {
                      free (last_device);
                      free (canon_dev);
                      break;
                    }
                  else
                    best_match_len = len;
                }
            }

          free (last_device);
        }

      free (canon_dev);
    }

  free (resolved);

  if (best_match)
    {
      get_dev (best_match->me_devname, best_match->me_mountdir, NULL,
               best_match->me_type, best_match->me_dummy,
               best_match->me_remote, NULL, false);
      return true;
    }
  else if (eclipsed_device)
    {
      error (0, 0, _("cannot access %s: over-mounted by another device"),
             quote (file));
      exit_status = EXIT_FAILURE;
      return true;
    }

  return false;
}
