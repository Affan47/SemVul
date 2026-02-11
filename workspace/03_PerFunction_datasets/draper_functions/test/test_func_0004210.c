pdes_init(char *keyfile)
{
    char keybuf[1024+1];
    int fd, res;
    des_cblock key_bin;


    if (keyfile == NULL)
    {
	errno = EINVAL;
	return -1;
    }

    fd = s_open(keyfile, O_RDONLY);
    if (fd < 0)
	return -1;

    res = s_read(fd, keybuf, sizeof(keybuf)-1);
    if (res != sizeof(keybuf)-1)
    {


	if (debug)
	    fprintf(stderr, "pdes: First key was not complete (%d bytes)\n",
		    res);

	s_close(fd);
	errno = EINVAL;
	return -1;
    }


    while ((res = s_read(fd, keybuf, sizeof(keybuf)-1)) == sizeof(keybuf)-1)
	;
    s_close(fd);

    if (res > 0 && res != sizeof(keybuf)-1)
    {


	if (debug)
	    fprintf(stderr, "pdes: Last key was not complete (%d bytes)\n",
		    res);

	errno = EINVAL;
	return -1;
    }

    keybuf[sizeof(keybuf)-1] = '\0';
    des_string_to_key(keybuf, &key_bin);
    des_set_key(&key_bin, sched);

    return 0;
}
