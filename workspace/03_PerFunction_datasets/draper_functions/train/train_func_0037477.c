gom_mixer_C_find(char * name)
{
	int c;
	for (c = gom_driver_C_first();
			 (gom_driver_C (c) > -1) && (strcmp (name, gom_driver_C_name(c, 0)) != 0);
			 c = gom_driver_C_next(c, +1));
	return c;
}
