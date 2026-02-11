python_initialize()
{
	PyObject *ekg, *ekg_config;
	Py_Initialize();

	PyImport_AddModule("ekg");
	if (!(ekg = Py_InitModule("ekg", ekg_methods)))
		return -1;

	ekg_config = PyObject_NEW(PyObject, &ekg_config_type);
	PyModule_AddObject(ekg, "config", ekg_config);


	PyModule_AddStringConstant(ekg, "VERSION", VERSION);


	PyModule_AddIntConstant(ekg, "MSGCLASS_MESSAGE",	EKG_MSGCLASS_MESSAGE);
	PyModule_AddIntConstant(ekg, "MSGCLASS_CHAT",		EKG_MSGCLASS_CHAT);
	PyModule_AddIntConstant(ekg, "MSGCLASS_SENT",		EKG_MSGCLASS_SENT);
	PyModule_AddIntConstant(ekg, "MSGCLASS_SENT_CHAT",	EKG_MSGCLASS_SENT_CHAT);
	PyModule_AddIntConstant(ekg, "MSGCLASS_SYSTEM",		EKG_MSGCLASS_SYSTEM);


	PyModule_AddStringConstant(ekg, "STATUS_NA",		(char *) ekg_status_string(EKG_STATUS_NA, 0));
	PyModule_AddStringConstant(ekg, "STATUS_AVAIL",		(char *) ekg_status_string(EKG_STATUS_AVAIL, 0));
	PyModule_AddStringConstant(ekg, "STATUS_AWAY",		(char *) ekg_status_string(EKG_STATUS_AWAY, 0));
	PyModule_AddStringConstant(ekg, "STATUS_AUTOAWAY",	(char *) ekg_status_string(EKG_STATUS_AUTOAWAY, 0));
	PyModule_AddStringConstant(ekg, "STATUS_INVISIBLE",	(char *) ekg_status_string(EKG_STATUS_INVISIBLE, 0));
	PyModule_AddStringConstant(ekg, "STATUS_XA",		(char *) ekg_status_string(EKG_STATUS_XA, 0));
	PyModule_AddStringConstant(ekg, "STATUS_DND",		(char *) ekg_status_string(EKG_STATUS_DND, 0));
	PyModule_AddStringConstant(ekg, "STATUS_FREE_FOR_CHAT",	(char *) ekg_status_string(EKG_STATUS_FFC, 0));
	PyModule_AddStringConstant(ekg, "STATUS_BLOCKED",	(char *) ekg_status_string(EKG_STATUS_BLOCKED, 0));
	PyModule_AddStringConstant(ekg, "STATUS_UNKNOWN",	(char *) ekg_status_string(EKG_STATUS_UNKNOWN, 0));
	PyModule_AddStringConstant(ekg, "STATUS_ERROR",		(char *) ekg_status_string(EKG_STATUS_ERROR, 0));


	PyModule_AddIntConstant(ekg, "IGNORE_STATUS",		IGNORE_STATUS);
	PyModule_AddIntConstant(ekg, "IGNORE_STATUS_DESCR",	IGNORE_STATUS_DESCR);
	PyModule_AddIntConstant(ekg, "IGNORE_MSG",		IGNORE_MSG);
	PyModule_AddIntConstant(ekg, "IGNORE_DCC",		IGNORE_DCC);
	PyModule_AddIntConstant(ekg, "IGNORE_EVENTS",		IGNORE_EVENTS);
	PyModule_AddIntConstant(ekg, "IGNORE_NOTIFY",		IGNORE_NOTIFY);
	PyModule_AddIntConstant(ekg, "IGNORE_XOSD",		IGNORE_XOSD);
	PyModule_AddIntConstant(ekg, "IGNORE_ALL",		IGNORE_ALL);


	PyModule_AddIntConstant(ekg, "WATCH_READ",		WATCH_READ);
	PyModule_AddIntConstant(ekg, "WATCH_READ_LINE",		WATCH_READ_LINE);
	PyModule_AddIntConstant(ekg, "WATCH_WRITE",		WATCH_WRITE);


	return 0;
}
