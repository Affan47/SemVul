create_fsel(const gchar *dirname, const gchar *filename, const gchar *ext, gboolean save)
{
#ifndef __WIN32__
	if(fs_type == 2)
	{
#if WITH_KDE
		const char *p = getenv("KDE_FULL_SESSION");
		if (p && *p)
			fs_type = 3;
		else
#endif
			fs_type = 1;
	}
#endif
#if !WITH_KDE
	if(fs_type == 3)
		fs_type = 1;
#endif


	switch(fs_type)
	{
	case 0:
	case 1:	return create_fsel_2(dirname, filename, ext, save);
	case 2: return create_fsel_3(dirname, filename, ext, save);
	case 3: return create_fsel_4(dirname, filename, ext, save);
	default: return NULL;
	}

	return NULL;
}
