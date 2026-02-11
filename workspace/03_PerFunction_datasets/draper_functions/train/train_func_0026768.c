GB_INIT(void)
{
	char *comp;
	char *env;

	env = getenv("GB_GUI");
	if (env)
	{
		comp = env;
		if (!GB.LoadComponent(env))
			return FALSE;
	}

	comp = "gb.gtk";

	env = getenv("KDE_FULL_SESSION");

	if (env && !strcmp(env, "true"))
	{
		env = getenv("KDE_SESSION_VERSION");
		if (env && !strcmp(env, "4"))
			comp = "gb.qt4";
	}

	if (GB.LoadComponent(comp))
		fprintf(stderr, "gb.gui: unable to load '%s' component\n", comp);

  return 0;
}
