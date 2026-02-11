vbi_open(char *vbi_name, struct cache *ca, int fine_tune, int big_buf, const char *progname, int txtpid)
{
    static int inited = 0;
    struct vbi *vbi;

    if (vbi_name == NULL)
    {
        int i;
        char *tried_devices = NULL;
        char *old_tried_devices = NULL;
        for (i = 0; vbi_names[i] != NULL; i++)
        {
            vbi_name = vbi_names[i];


            if (old_tried_devices)
            {
                if (asprintf(&tried_devices, "%s, %s", old_tried_devices, vbi_name) < 0)
                    tried_devices = NULL;
                free(old_tried_devices);
            }
            else if (asprintf(&tried_devices, "%s", vbi_name) < 0)
                tried_devices = NULL;
            if (tried_devices == NULL)
                out_of_mem(-1);
            old_tried_devices = tried_devices;

            if (access(vbi_name, R_OK) != 0)
                continue;
            vbi = vbi_open(vbi_name, ca, fine_tune, big_buf, progname, txtpid);
            if (vbi != NULL)
            {
                if (tried_devices != NULL)
                    free(tried_devices);
                return vbi;
            }
        }

	error("could not open any of the standard devices (%s)", tried_devices);
        free(tried_devices);
	return NULL;
    }

    if (not inited)
	lang_init();
    inited = 1;

    if (not(vbi = malloc(sizeof(*vbi))))
    {
	error("out of memory");
	goto fail1;
    }

    if (!vbi_dvb_open(vbi, vbi_name, progname, txtpid)) {
	    vbi->cache = ca;

	    dl_init(vbi->clients);
	    vbi->seq = 0;
	    out_of_sync(vbi);
	    vbi->ppage = vbi->rpage;


	    fdset_add_fd(fds, vbi->fd, dvb_handler, vbi);
	    return vbi;
    }
    if ((vbi->fd = open(vbi_name, O_RDONLY)) == -1)
	    {
		    ioerror(vbi_name);
		    goto fail2;
	    }

    if (big_buf != -1)
	    error("-oldbttv/-newbttv is obsolete.  option ignored.");

    if (setup_dev(vbi) == -1)
	    goto fail3;

    vbi->cache = ca;

    dl_init(vbi->clients);
    vbi->seq = 0;
    out_of_sync(vbi);
    vbi->ppage = vbi->rpage;

    vbi_pll_reset(vbi, fine_tune);
    fdset_add_fd(fds, vbi->fd, vbi_handler, vbi);
    return vbi;

fail3:
    close(vbi->fd);
fail2:
    free(vbi);
fail1:
    return 0;
}
