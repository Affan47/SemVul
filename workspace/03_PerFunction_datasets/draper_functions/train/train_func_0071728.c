WriteGame (char *filename, qboolean autosave)
{
	FILE *f;
	int i;
	char str[16];

	if (!autosave)
	SaveClientData ();

	f = fopen (filename, "wb");
	if (!f)
		gi.error ("Couldn't open %s", filename);

	memset (str, 0, sizeof (str));
	strcpy (str, __DATE__);
	fwrite (str, sizeof (str), 1, f);

	game.autosaved = autosave;
	fwrite (&game, sizeof (game), 1, f);
	game.autosaved = false;

	for (i = 0; i < game.maxclients; i++)
		WriteClient (f, &game.clients[i]);

	fclose (f);
}
