replay_open (void)
{
    char new_name[MAX_FILE_NAME + 1];

    if (os_read_file_name (new_name, command_name, FILE_PLAYBACK)) {

	strcpy (command_name, new_name);

	if ((pfp = fopen (new_name, "rt")) != NULL) {

	    set_more_prompts (read_yes_or_no ("Do you want MORE prompts"));

	    istream_replay = TRUE;

	} else print_string ("Cannot open file\n");

    }

}
