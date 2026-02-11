keymap_dump(ang_file *fff)
{
	size_t i;
	int mode;
	char buf[1024];

	if (OPT(rogue_like_commands))
		mode = KEYMAP_MODE_ROGUE;
	else
		mode = KEYMAP_MODE_ORIG;

	for (i = 0; i < N_ELEMENTS(keymap_act[mode]); i++)
	{
		char key[2] = "?";
		cptr act;


		act = keymap_act[mode][i];


		if (!act) continue;


		ascii_to_text(buf, sizeof(buf), act);


		file_putf(fff, "A:%s\n", buf);


		key[0] = i;


		ascii_to_text(buf, sizeof(buf), key);


		file_putf(fff, "C:%d:%s\n", mode, buf);


		file_putf(fff, "\n");
	}

}
