print_ganglia_25_config( char *path )
{
   configfile_t *configfile;
   FILE *fp;
   static configoption_t gmond_options[] =
      {
         {"name", ARG_STR, cb_name, &gmond_config, 0},
         {"owner", ARG_STR, cb_owner, &gmond_config, 0},
         {"latlong", ARG_STR, cb_latlong, &gmond_config, 0},
         {"url", ARG_STR, cb_url, &gmond_config, 0},
         {"location", ARG_STR, cb_location, &gmond_config, 0},
         {"mcast_channel", ARG_STR, cb_mcast_channel, &gmond_config, 0},
         {"mcast_port", ARG_INT, cb_mcast_port, &gmond_config, 0},
         {"mcast_if", ARG_STR, cb_mcast_if, &gmond_config, 0},
         {"mcast_ttl", ARG_INT, cb_mcast_ttl, &gmond_config, 0},
         {"mcast_threads", ARG_INT, cb_mcast_threads, &gmond_config, 0},
         {"xml_port", ARG_INT, cb_xml_port, &gmond_config, 0},
         {"xml_threads", ARG_INT, cb_xml_threads, &gmond_config, 0},
         {"trusted_hosts", ARG_LIST, cb_trusted_hosts, &gmond_config, 0},
         {"num_nodes", ARG_INT, cb_num_nodes, &gmond_config, 0},
         {"num_custom_metrics", ARG_INT, cb_num_custom_metrics, &gmond_config, 0},
         {"mute", ARG_TOGGLE, cb_mute, &gmond_config, 0},
         {"deaf", ARG_TOGGLE, cb_deaf, &gmond_config, 0},
         {"allow_extra_data", ARG_TOGGLE, cb_allow_extra_data, &gmond_config, 0},
         {"debug_level", ARG_INT, cb_debug_level, &gmond_config, 0},
         {"no_setuid", ARG_TOGGLE, cb_no_setuid, &gmond_config, 0},
         {"setuid", ARG_STR, cb_setuid, &gmond_config, 0},
         {"no_gexec", ARG_TOGGLE, cb_no_gexec, &gmond_config, 0},
         {"all_trusted", ARG_TOGGLE, cb_all_trusted, &gmond_config, 0},
         {"host_dmax", ARG_INT, cb_host_dmax, &gmond_config, 0},
         LAST_OPTION
      };

   if(!path)
     {
       return 1;
     }
   fp = fopen( path, "r");
   if(!fp)
     {
       fprintf(stderr,"Unable to open ganglia 2.5 configuration '%s'. Exiting.\n", path);
       return 1;
     }

   set_defaults(&gmond_config);

   configfile = dotconf_create(path, gmond_options, 0, CASE_INSENSITIVE);
   if(!configfile)
     {
       fprintf(stderr,"dotconf_create() error for configuration '%s'. Exiting.\n", path);
       return 1;
     }

   configfile->errorhandler = (dotconf_errorhandler_t) errorhandler;

   if (dotconf_command_loop(configfile) == 0)
      {
         dotconf_cleanup(configfile);
         return 1;
      }
   dotconf_cleanup(configfile);

   print_config(path, &gmond_config);
   return 0;
}
