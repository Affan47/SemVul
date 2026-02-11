init_plugin (Plugin *p)
{
#define ANAME "crypt"
	aname = _("crypt");

	p->signature = ANAME VERSION;
	p->menu_name = _("_En/decrypt..");
	p->description = _("Encrypt or decrypt selected items");
	p->icon = "plugin_"ANAME"_"E2IP".png";

	if (p->action == NULL)
	{

		gchar *action_name = g_strconcat (_A(5),".",aname,NULL);
		p->action = e2_plugins_action_register (action_name, E2_ACTION_TYPE_ITEM,
			_e2p_task_docrypt, NULL, FALSE, 0, NULL);

		session_opts.en_suffix = g_strdup (".enc");
		session_opts.de_suffix = g_strdup (".enc");


		if ((libhandle = dlopen ("liblzo2.so.2", RTLD_LAZY)) != NULL)
		{
			init_compress = dlsym (libhandle, "__lzo_init_v2");
			if (init_compress != NULL)
			{
				compress_buf = dlsym (libhandle, "lzo1x_1_compress");
				if (compress_buf != NULL)
				{
					decompress_buf = dlsym (libhandle, "lzo1x_decompress_safe");
					if (decompress_buf != NULL)
						compresslib = E2_CFLAGCOMPRESS | E2_CFLAGLZO;
					else
					{
						init_compress = NULL;
						compress_buf = NULL;
					}
				}
				else
					init_compress = NULL;
			}
			if (compresslib == E2_CFLAGNONE)
				dlclose (libhandle);
		}


		if (compresslib == E2_CFLAGNONE &&
			(libhandle = dlopen ("libz.so.1", RTLD_LAZY)) != NULL)
		{
			compress_buf = dlsym (libhandle, "compress2");
			if (compress_buf != NULL)
			{
				decompress_buf = dlsym (libhandle, "uncompress");
				if (decompress_buf != NULL)
					compresslib = E2_CFLAGCOMPRESS | E2_CFLAGZ;
				else
					compress_buf = NULL;
			}
			if (compresslib == E2_CFLAGNONE)
				dlclose (libhandle);
		}


		if (compresslib == E2_CFLAGNONE &&
			(libhandle = dlopen ("libbz2.so.1", RTLD_LAZY)) != NULL)
		{
			compress_buf = dlsym (libhandle, "BZ2_bzBuffToBuffCompress");
			if (compress_buf != NULL)
			{
				decompress_buf = dlsym (libhandle, "BZ2_bzBuffToBuffDecompress");
				if (decompress_buf != NULL)
					compresslib = E2_CFLAGCOMPRESS | E2_CFLAGBZ2;
				else
					compress_buf = NULL;
			}
			if (compresslib == E2_CFLAGNONE)
			{
				dlclose (libhandle);
				libhandle = NULL;
			}
		}

		printd (DEBUG, "masked lib-flags %0x", compresslib & E2_CFLAGLIBMASK);
		return TRUE;
	}
	return FALSE;
}
