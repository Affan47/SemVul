get_all_entries (void)
{
  struct mount_entry *me;

  filter_mount_list (show_all_fs);

  for (me = mount_list; me; me = me->me_next)
    get_dev (me->me_devname, me->me_mountdir, NULL, me->me_type,
             me->me_dummy, me->me_remote, NULL, true);
}
