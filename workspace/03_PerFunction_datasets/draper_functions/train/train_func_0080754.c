enchant_load_providers_in_dir (EnchantBroker * broker, const char *dir_name)
{
	GModule *module = NULL;
	GDir *dir;
	G_CONST_RETURN char *dir_entry;
	size_t entry_len, g_module_suffix_len;

	char * filename;

	EnchantProvider *provider;
	EnchantProviderInitFunc init_func;
	EnchantPreConfigureFunc conf_func;

	dir = g_dir_open (dir_name, 0, NULL);
	if (!dir)
		return;

	g_module_suffix_len = strlen (G_MODULE_SUFFIX);

	while ((dir_entry = g_dir_read_name (dir)) != NULL)
		{
			provider = 0;

			entry_len = strlen (dir_entry);
			if ((entry_len > g_module_suffix_len) &&
				!strcmp(dir_entry+(entry_len-g_module_suffix_len), G_MODULE_SUFFIX))
				{
#ifdef _WIN32

					UINT old_error_mode = SetErrorMode(SEM_FAILCRITICALERRORS);
#endif
					filename = g_build_filename (dir_name, dir_entry, NULL);

					module = g_module_open (filename, (GModuleFlags) 0);
					if (module)
						{
							if (g_module_symbol
								(module, "init_enchant_provider", (gpointer *) (&init_func))
								&& init_func)
								{
									provider = init_func ();
									if (!enchant_provider_is_valid(provider))
										{
											g_warning ("Error loading plugin: %s's init_enchant_provider returned invalid provider.\n", dir_entry);
											if(provider)
												{
													if(provider->dispose)
														provider->dispose(provider);

													provider = NULL;
												}
											g_module_close (module);
										}
								}
							else
								{
									g_module_close (module);
								}
						}
					else
						{
							g_warning ("Error loading plugin: %s\n", g_module_error());
						}

					g_free (filename);
#ifdef _WIN32

					SetErrorMode(old_error_mode);
#endif
				}
			if (provider)
				{


					if (g_module_symbol
						(module, "configure_enchant_provider", (gpointer *) (&conf_func))
						&& conf_func)
						{
							conf_func (provider, dir_name);
							if (!enchant_provider_is_valid(provider))
								{
									g_warning ("Error loading plugin: %s's configure_enchant_provider modified provider and it is now invalid.\n", dir_entry);
									if(provider->dispose)
										provider->dispose(provider);

									provider = NULL;
									g_module_close (module);
								}
						}
				}
			if (provider)
				{
					provider->enchant_private_data = (void *) module;
					provider->owner = broker;
					broker->provider_list = g_slist_append (broker->provider_list, (gpointer)provider);
				}
		}

	g_dir_close (dir);
}
