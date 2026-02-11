scriptlang_register(scriptlang_t *s)
{
	scriptlang_add(s);

	s->init();

	if (!in_autoexec)
		scripts_autoload(s);
	return 0;
}
