config_publish(void)
{
	gchar *ruleset;
	PyObject *module, *dict, *object, *result;


	module = PyImport_AddModule("__main__");
	dict = PyModule_GetDict(module);
	object = PyDict_GetItemString(dict, "rules");

	switch (cfg.ruleset)
	{
		case RULESET_OMNIBUS: ruleset = "omnibus"; break;
		case RULESET_OMNIBUS_ALT: ruleset = "omnibus_alt"; break;
		case RULESET_SPOT_HEARTS: ruleset = "spot_hearts"; break;
		case RULESET_STANDARD: default: ruleset = "standard"; break;

	}

	result = PyObject_CallMethod(object, "set", "siiii", ruleset, cfg.clubs_lead, cfg.hearts_break, cfg.queen_breaks_hearts, cfg.no_blood);

	Py_DECREF(result);
}
