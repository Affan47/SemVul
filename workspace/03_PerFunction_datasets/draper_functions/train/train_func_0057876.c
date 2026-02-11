ksmserver_workarround(FvwmWindow *fw)
{

	if (fw->name.name != NULL && fw->class.res_name != NULL &&
	    fw->icon_name.name != NULL && fw->class.res_class != NULL &&
	    strcmp(fw->name.name, "ksmserver") == 0 &&
	    strcmp(fw->class.res_class, "ksmserver") == 0 &&
	    strcmp(fw->icon_name.name, "ksmserver") == 0 &&
	    strcmp(fw->class.res_name, "unnamed") == 0)
	{
		int layer = 0;

		if (IS_TRANSIENT(fw))
		{
			layer = Scr.TopLayer + 2;
		}
		else
		{
			layer = Scr.TopLayer + 1;
		}
		new_layer(fw, layer);

		return 1;
	}

	return 0;
}
