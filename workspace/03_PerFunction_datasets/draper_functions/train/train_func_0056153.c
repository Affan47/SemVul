ppp_recv_config (int unit,int mru,u_int32_t asyncmap,int pcomp,int accomp)
  {
    u_int x;

    SYSDEBUG ((LOG_DEBUG, "recv_config: mru = %d\n", mru));


    if (!still_ppp())
      {
	return;
      }


    if (ioctl(ppp_fd, PPPIOCSMRU, (caddr_t) &mru) < 0)
      {
	if ( ! ok_error (errno))
	  {
	    syslog(LOG_ERR, "ioctl(PPPIOCSMRU): %m(%d)", errno);
	  }
      }

    SYSDEBUG ((LOG_DEBUG, "recv_config: asyncmap = %lx\n", asyncmap));
    if (ioctl(ppp_fd, PPPIOCSRASYNCMAP, (caddr_t) &asyncmap) < 0)
      {
        syslog(LOG_ERR, "ioctl(PPPIOCSRASYNCMAP): %m(%d)", errno);
	quit();
      }

    x = get_flags();
    x = !accomp? x | SC_REJ_COMP_AC: x &~ SC_REJ_COMP_AC;
    set_flags (x);
  }
