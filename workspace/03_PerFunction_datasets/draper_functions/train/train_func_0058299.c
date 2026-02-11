minus_rw_finalize ()
{ int saved_errno = errno;

    sigs_mask(SIGS_BLOCK);
    while (media_written)
    { Scsi_Command cmd(ioctl_handle);
      int err;

	fprintf (stderr,"%s: flushing cache\n",ioctl_device);
	if (flush_cache(cmd))	break;

	if (quickgrown)
	{   fprintf (stderr,"%s: writing lead-out\n",ioctl_device);
	    cmd[0] = 0x5B;
	    cmd[1] = 0x01;
	    cmd[2] = 0x02;
	    cmd[9] = 0;
	    if ((err=cmd.transport()))
		sperror ("CLOSE SESSION",err), saved_errno = errno;

	    if (wait_for_unit (cmd)) break;

	    quickgrown=0;
	}

	media_written = 0;
	next_wr_addr = 0;

	if (do_reload)
	{   if (media_reload())
		perror (":-( unable to reload tray");
	}
	else return;

	errno = saved_errno;
    }
    _exit (errno);
}
