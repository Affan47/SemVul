CMD_DestroyMenuStyle(F_CMD_ARGS)
{
	MenuStyle *ms = NULL;
	char *name = NULL;

	name = PeekToken(action, NULL);
	if (name == NULL)
	{
		fvwm_msg(ERR,"DestroyMenuStyle", "needs one parameter");
		return;
	}

	ms = menustyle_find(name);
	if (ms == NULL)
	{
		return;
	}
	else if (ms == menustyle_get_default_style())
	{
		fvwm_msg(ERR,"DestroyMenuStyle",
			 "cannot destroy default menu style. "
			 "To reset the default menu style use\n  %s",
			 DEFAULT_MENU_STYLE);
		return;
	}
	else if (ST_USAGE_COUNT(ms) != 0)
	{
		fvwm_msg(ERR, "DestroyMenuStyle", "menu style %s is in use",
			 name);
		return;
	}
	else
	{
		menustyle_free(ms);
	}
	menus_remove_style_from_menus(ms);

	return;
}
