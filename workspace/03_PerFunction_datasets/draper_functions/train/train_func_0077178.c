gamestate_save(state_t *s, char *dirname)
{
	FILE *fh;
	sci_dir_t dir;
	char *filename;
	int fd;

	_global_save_state = s;
	s->savegame_version = FREESCI_CURRENT_SAVEGAME_VERSION;
	s->dyn_views_list_serial = (s->dyn_views)? s->dyn_views->serial : -2;
	s->drop_views_list_serial = (s->drop_views)? s->drop_views->serial : -2;
	s->port_serial = (s->port)? s->port->serial : -2;

	if (s->execution_stack_base) {
		sciprintf("Cannot save from below kernel function\n");
		return 1;
	}

	scimkdir (dirname, 0700);

	if (chdir (dirname)) {
		sciprintf("Could not enter directory '%s'\n", dirname);
		return 1;
	}

	sci_init_dir(&dir);
	filename = sci_find_first(&dir, "*");
	while (filename) {
		if (strcmp(filename, "..") && strcmp(filename, "."))
			unlink(filename);
		filename = sci_find_next(&dir);
	}
	sci_finish_find(&dir);


	fh = fopen("state", "w" FO_TEXT);


	s->game_time = time(NULL) - s->game_start_time.tv_sec;

SCI_MEMTEST;

  _cfsml_write_state_t(fh, s);
  fprintf(fh, "\n");

SCI_MEMTEST;

	fclose(fh);

	_gamestate_unfrob(s);


	chdir ("..");
	return 0;
}
