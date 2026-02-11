sys_check_options(void)
  {
#ifdef IPX_CHANGE
    struct stat stat_buf;


    while (ipxcp_protent.enabled_flag)
      {
        if (path_to_procfs())
	  {
	    strcat (route_buffer, "/net/ipx_interface");
	    if (lstat (route_buffer, &stat_buf) >= 0)
	      {
		break;
	      }
	  }
	syslog (LOG_ERR, "IPX support is not present in the kernel\n");
	ipxcp_protent.enabled_flag = 0;
	ipcp_protent.enabled_flag  = 1;
	break;
      }
#endif
    if (demand && driver_is_old) {
      option_error("demand dialling is not supported by kernel driver version "
		   "%d.%d.%d", driver_version, driver_modification,
		   driver_patch);
      return 0;
    }
    return 1;
  }
