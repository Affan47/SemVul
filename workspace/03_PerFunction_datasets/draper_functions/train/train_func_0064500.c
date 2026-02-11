read_conf_files(int cold)
{
  const char *filename;
  char chanmodes[32];
  char chanlimit[32];

  conf_parser_ctx.boot = cold;
  filename = get_conf_name(CONF_TYPE);


  strlcpy(conffilebuf, filename, sizeof(conffilebuf));

  if ((conf_parser_ctx.conf_file = fbopen(filename, "r")) == NULL)
  {
    if (cold)
    {
      ilog(L_CRIT, "Unable to read configuration file '%s': %s",
           filename, strerror(errno));
      exit(-1);
    }
    else
    {
      sendto_realops_flags(UMODE_ALL, L_ALL,
			   "Unable to read configuration file '%s': %s",
			   filename, strerror(errno));
      return;
    }
  }

  if (!cold)
    clear_out_old_conf();

  read_conf(conf_parser_ctx.conf_file);
  fbclose(conf_parser_ctx.conf_file);

  add_isupport("NETWORK", ServerInfo.network_name, -1);
  snprintf(chanmodes, sizeof(chanmodes), "b%s%s:%d",
           ConfigChannel.use_except ? "e" : "",
           ConfigChannel.use_invex ? "I" : "", ConfigChannel.max_bans);
  add_isupport("MAXLIST", chanmodes, -1);
  add_isupport("MAXTARGETS", NULL, ConfigFileEntry.max_targets);

  if (ConfigChannel.disable_local_channels)
    add_isupport("CHANTYPES", "#", -1);
  else
    add_isupport("CHANTYPES", "#&", -1);

  snprintf(chanlimit, sizeof(chanlimit), "%s:%d",
           ConfigChannel.disable_local_channels ? "#" : "#&",
	   ConfigChannel.max_chans_per_user);
  add_isupport("CHANLIMIT", chanlimit, -1);
  snprintf(chanmodes, sizeof(chanmodes), "%s%s%s",
           ConfigChannel.use_except ? "e" : "",
	   ConfigChannel.use_invex ? "I" : "", "b,k,l,aimnrstxy");
  add_isupport("CHANNELLEN", NULL, LOCAL_CHANNELLEN);

  if (ConfigChannel.use_except)
    add_isupport("EXCEPTS", "e", -1);
  if (ConfigChannel.use_invex)
    add_isupport("INVEX", "I", -1);
  add_isupport("CHANMODES", chanmodes, -1);


  rebuild_isupport_message_line();

#ifdef HAVE_LIBPCRE
  parse_conf_file(RKLINE_TYPE, cold);
  parse_conf_file(RXLINE_TYPE, cold);
#endif
  parse_conf_file(KLINE_TYPE, cold);
  parse_conf_file(DLINE_TYPE, cold);
  parse_conf_file(XLINE_TYPE, cold);
  parse_conf_file(NRESV_TYPE, cold);
  parse_conf_file(CRESV_TYPE, cold);
}
