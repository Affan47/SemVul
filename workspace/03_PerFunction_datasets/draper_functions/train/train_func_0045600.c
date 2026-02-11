set_chroot(void)
{
    char *absdir;
    int abslen;
    char *logdir;

    logdir = get_abs_path(logpath);


    if(chdir(chroot_dir) != 0)
    {
        fatal("set_chroot: Can not chdir to \"%s\": %s\n", chroot_dir,
              strerror(errno));
    }


    absdir = getcwd(NULL, 0);
    abslen = strlen(absdir);


    if(chroot(absdir) < 0)
    {
        fatal("Can not chroot to \"%s\": absolute: %s: %s\n",
               chroot_dir, absdir, strerror(errno));
    }

    if(chdir("/") < 0)
    {
        fatal("Can not chdir to \"/\" after chroot: %s\n",
               strerror(errno));
    }

    return 0;
}
