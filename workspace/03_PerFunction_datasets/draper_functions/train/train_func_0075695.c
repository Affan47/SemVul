Options_Menu_Reinitialize (void)
{
	int i;
	for (i = 0; i < last_options_menu_nitems; i++)
		Option_Setup (&last_options_menu->widgets[i], &last_options_menu_namelist[i]);
}
