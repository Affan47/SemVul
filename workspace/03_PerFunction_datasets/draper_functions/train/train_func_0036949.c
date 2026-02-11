execenv(env, arg)
CONST char *env, *arg;
{
	char *command;

	if (!(command = getenv2(env)) || !*command) return(0);
	clearscreen();
	ptymacro(command, arg, F_NOCONFIRM | F_IGNORELIST);

	return(1);
}
