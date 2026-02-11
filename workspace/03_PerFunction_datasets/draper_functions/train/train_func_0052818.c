lis_sig(void)
{
    static int stat = 0;
    int stat_read;

  if ( config.flux==3 )
  {

    Set_signals( 1 );
  }

    if(serial_port_fd != -1)
    {
	if(ioctl(serial_port_fd, TIOCMGET, &stat_read) == -1)
	{


	    if (errno != EINVAL)
	    {
		i18n_perror(_("Control signals read"));
		Ferme_Port();
	    }

	    return -2;
	}

	if(stat_read == stat)
	    return -1;

	stat = stat_read;

	return stat;
    }
    return -1;
}
