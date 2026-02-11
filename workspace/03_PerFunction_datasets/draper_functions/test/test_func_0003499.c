filter_mount_list (bool devices_only)
{
  struct mount_entry *me;


  for (me = mount_list; me;)
    {
      struct stat buf;
      struct devlist *devlist;
      struct mount_entry *discard_me = NULL;


      if ((me->me_remote && show_local_fs)
          || -1 == stat (me->me_mountdir, &buf))
        {


          buf.st_dev = me->me_dev;
        }
      else
        {

          for (devlist = device_list; devlist; devlist = devlist->next)
            if (devlist->dev_num == buf.st_dev)
              break;

          if (devlist)
            {
              bool target_nearer_root = strlen (devlist->me->me_mountdir)
                                        > strlen (me->me_mountdir);

              bool source_below_root = devlist->me->me_mntroot != NULL
                                       && me->me_mntroot != NULL
                                       && (strlen (devlist->me->me_mntroot)
                                           < strlen (me->me_mntroot));
              if (! print_grand_total && me->me_remote && devlist->me->me_remote
                  && ! STREQ (devlist->me->me_devname, me->me_devname))
                {


                }
              else if ((strchr (me->me_devname, '/')

                        && ! strchr (devlist->me->me_devname, '/'))

                       || (target_nearer_root && ! source_below_root)

                       || (! STREQ (devlist->me->me_devname, me->me_devname)


                           && STREQ (me->me_mountdir,
                                     devlist->me->me_mountdir)))
                {

                  discard_me = devlist->me;
                  devlist->me = me;
                }
              else
                {

                  discard_me = me;
                }

            }
        }

      if (discard_me)
        {
          me = me->me_next;
          if (! devices_only)
            free_mount_entry (discard_me);
        }
      else
        {

          devlist = xmalloc (sizeof *devlist);
          devlist->me = me;
          devlist->dev_num = buf.st_dev;
          devlist->next = device_list;
          device_list = devlist;

          me = me->me_next;
        }
    }


  if (! devices_only) {
    mount_list = NULL;
    while (device_list)
      {

        me = device_list->me;
        me->me_next = mount_list;
        mount_list = me;

        struct devlist *devlist = device_list->next;
        free (device_list);
        device_list = devlist;
      }
  }
}
