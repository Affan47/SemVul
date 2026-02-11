send_desktop_names(fmodule *module)
{
	DesktopsInfo *d;
	char *name;

	for (d = Scr.Desktops->next; d != NULL; d = d->next)
	{
		if (d->name != NULL)
		{
			name = (char *)safemalloc(strlen(d->name) + 44);
			sprintf(name,"DesktopName %d %s", d->desk, d->name);
			SendName(module, M_CONFIG_INFO, 0, 0, 0, name);
			free(name);
		}
	}

	return;
}
