handle_hot_key (zchar key)
{

    if (cwin == 0) {

	bool aborting;

	aborting = FALSE;

	print_string ("\nHot key -- ");

	switch (key) {
	    case ZC_HKEY_RECORD: aborting = hot_key_recording (); break;
	    case ZC_HKEY_PLAYBACK: aborting = hot_key_playback (); break;
	    case ZC_HKEY_SEED: aborting = hot_key_seed (); break;
	    case ZC_HKEY_UNDO: aborting = hot_key_undo (); break;
	    case ZC_HKEY_RESTART: aborting = hot_key_restart (); break;
	    case ZC_HKEY_QUIT: aborting = hot_key_quit (); break;
	    case ZC_HKEY_DEBUG: aborting = hot_key_debugging (); break;
	    case ZC_HKEY_HELP: aborting = hot_key_help (); break;
	}

	if (aborting)
	    return TRUE;

	print_string ("\nContinue input...\n");

    }

    return FALSE;

}
