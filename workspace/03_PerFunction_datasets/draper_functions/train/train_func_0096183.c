update(void)
{
	STATIC_STRBUF(command);

	strbuf_clear(command);
	strbuf_sprintf(command, "%s -u", global_path);
	if (vflag) {
		strbuf_putc(command, 'v');
		fprintf(stderr, "gscope: %s\n", strbuf_value(command));
	}
	system(strbuf_value(command));
}
