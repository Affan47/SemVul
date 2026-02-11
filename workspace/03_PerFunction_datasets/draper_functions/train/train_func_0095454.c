category_load_csv(gchar *filename, gchar **error)
{
gboolean retval;
GIOChannel *io;
gchar *tmpstr;
gint io_stat;
gchar **str_array;
gchar *lastcatname = NULL;
gchar *fullcatname;
GError *err = NULL;
Category *item;
gint type = 0;
const gchar *encoding;

	encoding = homebank_file_getencoding(filename);

			DB( g_print(" -> encoding should be %s\n", encoding) );


	retval = TRUE;
	*error = NULL;
	io = g_io_channel_new_file(filename, "r", NULL);
	if(io != NULL)
	{

		if( encoding != NULL )
		{
			g_io_channel_set_encoding(io, encoding, NULL);
		}

		for(;;)
		{
			if( *error != NULL )
				break;
			io_stat = g_io_channel_read_line(io, &tmpstr, NULL, NULL, &err);

			DB( g_print(" + iostat %d\n", io_stat) );

			if( io_stat == G_IO_STATUS_ERROR )
			{
				DB (g_print(" + ERROR %s\n",err->message));
				break;
			}
			if( io_stat == G_IO_STATUS_EOF)
				break;
			if( io_stat == G_IO_STATUS_NORMAL)
			{
				if( tmpstr != NULL )
				{
					DB( g_print(" + strip %s\n", tmpstr) );

					hb_string_strip_crlf(tmpstr);

					DB( g_print(" + split\n") );

					str_array = g_strsplit (tmpstr, ";", 3);


					if( g_strv_length (str_array) != 3 )
					{
						*error = _("invalid csv format");
						retval = FALSE;
						DB( g_print(" + error %s\n", *error) );
					}
					else
					{
						DB( g_print(" + read %s : %s : %s\n", str_array[0], str_array[1], str_array[2]) );

						fullcatname = NULL;
						if( g_str_has_prefix(str_array[0], "1") )
						{
							fullcatname = g_strdup(str_array[2]);
							g_free(lastcatname);
							lastcatname = g_strdup(str_array[2]);

							type = g_str_has_prefix(str_array[1], "+") ? GF_INCOME : 0;

							DB( g_print(" + type = %d\n", type) );

						}
						else
						if( g_str_has_prefix(str_array[0], "2") )
						{
							fullcatname = g_strdup_printf("%s:%s", lastcatname, str_array[2]);
						}

						DB( g_print(" + fullcatname %s\n", fullcatname) );

						item = da_cat_append_ifnew_by_fullname(fullcatname, FALSE);

						DB( g_print(" + item %p\n", item) );

						if( item != NULL)
						{
							DB( g_print(" + assign flags: '%c'\n", type) );

							item->flags |= type;

						}

						g_free(fullcatname);
						g_strfreev (str_array);
					}
				}

			}
			g_free(tmpstr);

		}
		g_io_channel_unref (io);


	}

	g_free(lastcatname);

	return retval;
}
