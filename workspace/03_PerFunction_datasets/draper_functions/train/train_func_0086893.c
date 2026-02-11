parse_mode_update(const char *name, gint mode, gint value)
{
	char *pm_name = parse_mode_pm_name(name);
	ParseMode *pm = (ParseMode *) array_find(parse_modes, pm_name, FALSE);

	if (!pm)
	{
		pm = (ParseMode *) array_append(parse_modes);
		pm->name = g_strdup(pm_name);
		pm->hb_mode = HB_DEFAULT;
		pm->mr_mode = MR_DEFAULT;
		pm->entry = TRUE;
	}
	g_free(pm_name);

	switch (mode)
	{
		case MODE_HBIT : pm->hb_mode = value; break;
		case MODE_MEMBER : pm->mr_mode = value; break;
		default :
		{
			g_assert(mode == MODE_ENTRY);
			pm->entry = value;
		}
	}

	if (pm->hb_mode == HB_DEFAULT && pm->mr_mode == MR_DEFAULT && pm->entry)
		array_remove(parse_modes, pm);
}
