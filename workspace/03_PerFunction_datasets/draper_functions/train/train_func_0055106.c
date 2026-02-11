shell_exec_memory_usage(struct gnutella_shell *sh,
	int argc, const char *argv[])
{
	shell_check(sh);
	g_assert(argv);
	g_assert(argc > 0);

	if (argc < 2)
		return REPLY_ERROR;

#define CMD(name) G_STMT_START { \
	if (0 == ascii_strcasecmp(argv[1], #name)) \
		return shell_exec_memory_usage_## name(sh, argc - 1, argv + 1); \
} G_STMT_END

	CMD(zone);

#undef CMD

	shell_set_formatted(sh, _("Unknown operation \"usage %s\""), argv[1]);
	return REPLY_ERROR;
}
