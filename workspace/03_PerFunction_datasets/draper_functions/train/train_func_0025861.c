gconf_server_get_default_sources(void)
{
  GSList* addresses;
  GList* tmp;
  gboolean have_writable = FALSE;
  gchar* conffile;
  GConfSources* sources = NULL;
  GError* error = NULL;

  conffile = g_strconcat(GCONF_CONFDIR, "/path", NULL);

  addresses = gconf_load_source_path(conffile, NULL);

  g_free(conffile);

#ifdef GCONF_ENABLE_DEBUG


  if (addresses == NULL)
    {
      gconf_log(GCL_DEBUG, _("gconfd compiled with debugging; trying to load gconf.path from the source directory"));
      conffile = g_strconcat(GCONF_SRCDIR, "/gconf/gconf.path", NULL);
      addresses = gconf_load_source_path(conffile, NULL);
      g_free(conffile);
    }


#endif

  if (addresses == NULL)
    {
      const char *configdir = g_get_user_config_dir ();


      addresses = g_slist_append(addresses, g_strconcat("xml:readwrite:", configdir, "/gconf", NULL));

      gconf_log(GCL_DEBUG, _("No configuration files found. Trying to use the default configuration source `%s'"), (char *)addresses->data);
    }

  if (addresses == NULL)
    {


      gconf_log(GCL_ERR, _("No configuration sources in the source path. Configuration won't be saved; edit %s%s"), GCONF_CONFDIR, "/path");

      sources = gconf_sources_new_from_addresses(NULL, NULL);

      return sources;
    }
  else
    {
      sources = gconf_sources_new_from_addresses(addresses, &error);

      if (error != NULL)
        {
          gconf_log(GCL_ERR, _("Error loading some configuration sources: %s"),
                    error->message);

          g_error_free(error);
          error = NULL;
        }

      gconf_address_list_free(addresses);

      g_assert(sources != NULL);

      if (sources->sources == NULL)
        gconf_log(GCL_ERR, _("No configuration source addresses successfully resolved. Can't load or store configuration data"));

      tmp = sources->sources;

      while (tmp != NULL)
        {
          if (((GConfSource*)tmp->data)->flags & GCONF_SOURCE_ALL_WRITEABLE)
            {
              have_writable = TRUE;
              break;
            }

          tmp = g_list_next(tmp);
        }


      if (!have_writable)
        gconf_log(GCL_WARNING, _("No writable configuration sources successfully resolved. May be unable to save some configuration changes"));

      return sources;
    }
}
