close_tun (struct tuntap *tt)
{
  if (tt)
    {
	if (tt->type != DEV_TYPE_NULL && tt->did_ifconfig)
	  {
	    struct argv argv;
	    struct gc_arena gc = gc_new ();
	    argv_init (&argv);

#ifdef CONFIG_FEATURE_IPROUTE
	    if (is_tun_p2p (tt))
	      {
		argv_printf (&argv,
			"%s addr del dev %s local %s peer %s",
			iproute_path,
			tt->actual_name,
			print_in_addr_t (tt->local, 0, &gc),
			print_in_addr_t (tt->remote_netmask, 0, &gc)
			);
	      }
	    else
	      {
		argv_printf (&argv,
			"%s addr del dev %s %s/%d",
			iproute_path,
			tt->actual_name,
			print_in_addr_t (tt->local, 0, &gc),
			count_netmask_bits(print_in_addr_t (tt->remote_netmask, 0, &gc))
			);
	      }
#else
	    argv_printf (&argv,
			"%s %s 0.0.0.0",
			IFCONFIG_PATH,
			tt->actual_name
			);
#endif

	    argv_msg (M_INFO, &argv);
	    openvpn_execve_check (&argv, NULL, 0, "Linux ip addr del failed");

	    argv_reset (&argv);
	    gc_free (&gc);
	  }
      close_tun_generic (tt);
      free (tt);
    }
}
