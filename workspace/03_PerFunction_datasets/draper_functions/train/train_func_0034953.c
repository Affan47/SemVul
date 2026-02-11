print_game_history(int OUTPUT_XML, FILE* out, const struct GameDriver* game)
{
	char buffer[HISTORY_BUFFER_MAX];

	if (load_driver_history(game,buffer,HISTORY_BUFFER_MAX)==0)
	{
		fprintf(out, SELECT(L1P "history ", "\t\t<history>"));
		print_free_string(OUTPUT_XML, out, buffer);
		fprintf(out, SELECT(L1N, "</history>\n"));
	}
}
