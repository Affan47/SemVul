load_config(prefs_t *p)
{
	FILE *f = fmap->fopen(KOBO_CONFIG_DIR "/" KOBO_CONFIG_FILE, "r");
	if(f)
	{
		p->read(f);
		fclose(f);
	}
}
