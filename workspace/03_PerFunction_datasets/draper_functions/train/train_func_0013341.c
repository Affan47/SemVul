filesystem_available (const char *filesystem)
{
  int r;

  r = test_proc_filesystems (filesystem);
  if (r == -1 || r > 0)
    return r;


  if (optgroup_linuxmodules_available ()) {
    modprobe (filesystem);

    r = test_proc_filesystems (filesystem);
    if (r == -1)
      return -1;
  }

  return r;
}
