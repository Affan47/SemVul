boot_entry(menu_t *menu_ptr, char *arg)
{
  void *kernel, *initrd_buf;
  ssize_t kernel_size = 0, initrd_size = 0;
  struct initramfs *initrd = NULL;
  char *file, *cmd_buf;
  int fd;
  struct stat sbuf;
  char *s, *s0, *t, *initrd_arg;

  if(!menu_ptr) return;

  if(menu_ptr->localboot) {
    gfx_done();
    syslinux_local_boot(strtol(menu_ptr->localboot, NULL, 0));

    return;
  }

  file = menu_ptr->alt_kernel;
  if(!file) file = menu_ptr->kernel;
  if(!file) file = menu_ptr->linux;
  if(!file) {
    gfx_done();
    asprintf(&cmd_buf, "%s %s", menu_ptr->label, arg);
    syslinux_run_command(cmd_buf);
    return;
  }


  kernel_size = 0;

  if((fd = open(file, O_RDONLY)) >= 0) {
    if(!fstat(fd, &sbuf) && S_ISREG(sbuf.st_mode)) kernel_size = sbuf.st_size;
    close(fd);
  }

  gfx_progress_init(kernel_size, file);

  kernel = load_one(file, &kernel_size);

  if(!kernel) {
    return;
  }

  if(kernel_size < 1024 || *(uint32_t *) (kernel + 0x202) != 0x53726448) {

    gfx_done();
    asprintf(&cmd_buf, "%s %s", menu_ptr->label, arg);
    syslinux_run_command(cmd_buf);
    return;
  }


  initrd_arg = menu_ptr->initrd;

  s = s0 = strdup(arg);

  while(*s && strncmp(s, "initrd=", sizeof "initrd=" - 1)) {
    s = skipspace(skip_nonspaces(s));
  }

  if(*s) {
    s += sizeof "initrd=" - 1;
    *skip_nonspaces(s) = 0;
    initrd_arg = s;
  }
  else if(initrd_arg) {
    free(s0);
    initrd_arg = s0 = strdup(initrd_arg);
  }

  if(initrd_arg) {
    initrd = initramfs_init();

    while((t = strsep(&initrd_arg, ","))) {
      initrd_buf = load_one(t, &initrd_size);

      if(!initrd_buf) {
        printf("%s: read error\n", t);
        free(s0);
        return;
      }

      initramfs_add_data(initrd, initrd_buf, initrd_size, initrd_size, 4);


    }
  }

  free(s0);

  gfx_done();

  syslinux_boot_linux(kernel, kernel_size, initrd, arg);
}
