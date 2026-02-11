initialize()
{
	if(initialized)
		return;

	init();
	set_defaults();
	build_table();
	initialized = 1;
}
