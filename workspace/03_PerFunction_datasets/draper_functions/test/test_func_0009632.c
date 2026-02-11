save(const char *path, int quality)
{
	bool ok=false;
	int b;
	char *type;
	const char *buf=NULL;
	GSList *formats = gdk_pixbuf_get_formats();
	GSList *iter=formats;
	GdkPixbuf *image = getPixbuf();
	char arg[16];

	for (b=strlen(path)-1;b>=0;b--)
		if (path[b]=='.') { buf=path+b+1; break; }

	if (!buf) return -1;

	while (iter && (!ok) )
	{
		if (gdk_pixbuf_format_is_writable ((GdkPixbufFormat*)iter->data))
		{
			type=gdk_pixbuf_format_get_name((GdkPixbufFormat*)iter->data);
			if (!strcasecmp(type,buf))
			{
				ok=true;
				break;
			}
			else
				g_free(type);
		}
		iter=iter->next;
	}

	if (!ok)
	{
		g_slist_free(formats);
		if (!strcasecmp("jpg", buf))
			type = (char *)"jpeg";
		else
			return -1;
	}

	if (quality >= 0)
	{
		sprintf(arg, "%d", quality);
		b = gdk_pixbuf_save(image, path, type, NULL, "quality", arg, (void *)NULL);
	}
	else
		b = gdk_pixbuf_save(image, path, type, NULL, (void *)NULL);


	if (ok) {
		g_free(type);
		g_slist_free(formats);
	}

	if (!b) return -2;
	return 0;
}
