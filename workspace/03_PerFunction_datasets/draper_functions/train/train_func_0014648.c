g_message(const char *s) {
	GLEInterface* iface = GLEGetInterfacePointer();
	if (!g.console_output) {
		g.console_output = true;
		if (g.needs_newline) iface->getOutput()->println();
	}
	iface->getOutput()->println(s);
}
