shell_cmd_get_handler(const char *cmd)
{
	static const struct {
		const char * const cmd;
		shell_cmd_handler_t handler;
	} commands[] = {
#define SHELL_CMD(x)	{ #x, shell_exec_ ## x },
#include "cmd.inc"
#undef	SHELL_CMD
	};
	size_t i;

	g_return_val_if_fail(cmd, NULL);

	for (i = 0; i < G_N_ELEMENTS(commands); i++) {
		if (ascii_strcasecmp(commands[i].cmd, cmd) == 0)
			return commands[i].handler;
	}
	return NULL;
}
