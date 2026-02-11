qemu_create_arch_serialdevice(const char* basedir, const char* arch)
{
  dev_t consoledev;

  if (!strcmp(arch, "arm") ||
      !strcmp(arch, "armel"))
    {
      consoledev = makedev(204, 64);
    }
  else
    {
      consoledev = makedev(4, 64);
    }
  return mknod_inside_chroot(basedir, "dev/console", S_IFCHR | 0660, consoledev);
}
