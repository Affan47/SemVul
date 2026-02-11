read_route_table (struct rtentry *rt)
  {
    static char delims[] = " \t\n";
    char *dev_ptr, *dst_ptr, *gw_ptr, *flag_ptr;

    memset (rt, '\0', sizeof (struct rtentry));

    for (;;)
      {
	if (fgets (route_buffer, sizeof (route_buffer), route_fd) ==
	    (char *) 0)
	  {
	    return 0;
	  }

	dev_ptr  = strtok (route_buffer, delims);
	dst_ptr  = strtok (NULL,         delims);
	gw_ptr   = strtok (NULL,         delims);
	flag_ptr = strtok (NULL,         delims);

	if (flag_ptr == (char *) 0)
	  {
	    return 0;
	  }


	if (isxdigit (*dst_ptr) && isxdigit (*gw_ptr) && isxdigit (*flag_ptr))
	  {
	    break;
	  }
      }

    ((struct sockaddr_in *) &rt->rt_dst)->sin_addr.s_addr =
      strtoul (dst_ptr, NULL, 16);

    ((struct sockaddr_in *) &rt->rt_gateway)->sin_addr.s_addr =
      strtoul (gw_ptr, NULL, 16);

    rt->rt_flags = (short) strtoul (flag_ptr, NULL, 16);
    rt->rt_dev   = dev_ptr;

    return 1;
  }
