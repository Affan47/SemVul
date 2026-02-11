CTFCheckRules(void)
{
	if (capturelimit->value && (ctfgame.team1 >= capturelimit->value || ctfgame.team2 >= capturelimit->value)) {
		gi.bprintf(PRINT_HIGH, "Capturelimit hit.\n");
		IRC_printf(IRC_T_GAME, "Capturelimit hit.\n");
		return true;
	}
	return false;
}
