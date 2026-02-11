init_capture (void)
{
  gchar *device;
  gchar ebuf[PCAP_ERRBUF_SIZE];
  unsigned int linktype;
  static gchar errorbuf[300];
  static gboolean data_initialized = FALSE;

  if (!data_initialized)
    {

      if (pref.name_res)
	{
	  if (dns_open ())
            g_warning ("Name resolver not available");
	}

      capture_status = STOP;
      data_initialized = TRUE;
    }

  device = appdata.interface;
  if (!device && !appdata.input_file)
    {
      *ebuf = '\0';
      device = g_strdup (pcap_lookupdev (ebuf));
      if (device == NULL)
	{
	  snprintf (errorbuf, sizeof(errorbuf),
                    _("No capture device found or insufficient privileges.\n"
                      "Only file replay will be available.\n"
                      "EtherApe must be run with administrative privileges "
                      "(e.g. root) to enable live capture.\n"
                      "Pcap error: %s"), ebuf);
	  return errorbuf;
	}


      appdata.interface = device;
    }


  if (!appdata.input_file)
    {
      *ebuf = '\0';
      if (!
	  (pch_struct =
	   pcap_open_live (device, MAXSIZE, TRUE, PCAP_TIMEOUT, ebuf)))
	{
	  snprintf (errorbuf, sizeof(errorbuf),
		   _("Error opening %s : %s\n- perhaps you need to be root?"),
		   device, ebuf);
	  return errorbuf;
	}
      pcap_fd = pcap_fileno (pch_struct);
      g_my_info (_("Live device %s opened for capture. pcap_fd: %d"), device,
		 pcap_fd);
    }
  else
    {
      if (device)
	{
	  snprintf (errorbuf, sizeof(errorbuf),
		   _("Can't open both %s and device %s. Please choose one."),
		   appdata.input_file, device);
	  return errorbuf;
	}
      *ebuf = '\0';
      if (!(pch_struct = pcap_open_offline (appdata.input_file, ebuf)))
	{
	  snprintf (errorbuf, sizeof(errorbuf),
                  _("Error opening %s : %s"), appdata.input_file, ebuf);
	  return errorbuf;
	}
      g_my_info (_("%s opened for offline capture"), appdata.input_file);

    }

  linktype = pcap_datalink(pch_struct);
  if (!setup_link_type(linktype))
    {
      if (appdata.input_file)
        {
          snprintf (errorbuf, sizeof(errorbuf),
                    _("File %s contains packets with unsupported "
                      "link type %d, cannot replay"),
                    appdata.input_file,
                    linktype);
        }
      else if (device)
        {
          snprintf (errorbuf, sizeof(errorbuf),
                    _("Device %s uses unsupported link type %d,"
                      "cannot capture. Please choose another interface."),
                    device,
                    linktype);
        }
      else
        {
          snprintf (errorbuf, sizeof(errorbuf), _("Unsupported link type %d"),
                    linktype);
        }
        return errorbuf;
    }

  if (appdata.mode == APEMODE_DEFAULT)
    {
      appdata.mode = IP;
      g_free (pref.filter);
      pref.filter = get_default_filter(appdata.mode);
    }
  if (appdata.mode == LINK6 && !has_linklevel())
    {
      snprintf (errorbuf, sizeof(errorbuf), _("This device does not support link-layer mode. "
                                              "Please use IP or TCP modes."));
      return errorbuf;
    }

  if (pref.filter)
    set_filter (pref.filter, device);

  return NULL;
}
