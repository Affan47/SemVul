initjack_mixer_c(void)
{
	PyObject *m;

	if (PyType_Ready(&MixerType) < 0)
		return;
	if (PyType_Ready(&ChannelType) < 0)
		return;
	if (PyType_Ready(&OutputChannelType) < 0)
		return;
	if (PyType_Ready(&ScaleType) < 0)
		return;

	m = Py_InitModule3("jack_mixer_c", jack_mixer_methods, "Jack Mixer C Helper Module");

	Py_INCREF(&MixerType);
	PyModule_AddObject(m, "Mixer", (PyObject*)&MixerType);
	Py_INCREF(&ChannelType);
	PyModule_AddObject(m, "Channel", (PyObject*)&ChannelType);
	Py_INCREF(&OutputChannelType);
	PyModule_AddObject(m, "OutputChannel", (PyObject*)&OutputChannelType);
	Py_INCREF(&ScaleType);
	PyModule_AddObject(m, "Scale", (PyObject*)&ScaleType);
}
