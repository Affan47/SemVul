print_game_bios(int OUTPUT_XML, FILE* out, const struct GameDriver* game)
{
	const struct SystemBios *thisbios;

	if(!game->bios)
		return;

	thisbios = game->bios;


	while(!BIOSENTRY_ISEND(thisbios))
	{
		fprintf(out, SELECT(L1P "biosset" L2B, "\t\t<biosset"));

		if (thisbios->_name)
			fprintf(out, SELECT(L2P "name %s" L2N, " name=\"%s\""), thisbios->_name);
		if (thisbios->_description)
			fprintf(out, SELECT(L2P "description \"%s\"" L2N, " description=\"%s\""), thisbios->_description);
		if (thisbios->value == 0)
			fprintf(out, SELECT(L2P "default yes" L2N, " default=\"yes\""));

		fprintf(out, SELECT(L2E L1N, "/>\n"));

		thisbios++;
	}
}
