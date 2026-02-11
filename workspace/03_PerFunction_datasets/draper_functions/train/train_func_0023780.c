do_statusbar_prev_word(bool allow_punct)
{
    size_t pww_save = statusbar_pww;
    char *char_mb;
    int char_mb_len;
    bool begin_line = FALSE, started_on_word = FALSE;

    assert(answer != NULL);

    char_mb = charalloc(mb_cur_max());


    while (!begin_line) {
	char_mb_len = parse_mbchar(answer + statusbar_x, char_mb, NULL);


	if (!is_word_mbchar(char_mb, allow_punct))
	    break;


	started_on_word = TRUE;

	if (statusbar_x == 0)
	    begin_line = TRUE;
	else
	    statusbar_x = move_mbleft(answer, statusbar_x);
    }


    if (statusbar_x == 0)
	begin_line = TRUE;
    else
	statusbar_x = move_mbleft(answer, statusbar_x);

    while (!begin_line) {
	char_mb_len = parse_mbchar(answer + statusbar_x, char_mb, NULL);


	if (is_word_mbchar(char_mb, allow_punct))
	    break;

	if (statusbar_x == 0)
	    begin_line = TRUE;
	else
	    statusbar_x = move_mbleft(answer, statusbar_x);
    }


    if (!begin_line) {
	if (statusbar_x == 0)
	    begin_line = TRUE;
	else
	    statusbar_x = move_mbleft(answer, statusbar_x);

	while (!begin_line) {
	    char_mb_len = parse_mbchar(answer + statusbar_x, char_mb,
		NULL);


	    if (!is_word_mbchar(char_mb, allow_punct))
		break;

	    if (statusbar_x == 0)
		begin_line = TRUE;
	    else
		statusbar_x = move_mbleft(answer, statusbar_x);
	}


	if (!begin_line)
	    statusbar_x += char_mb_len;
    }

    free(char_mb);

    statusbar_pww = statusbar_xplustabs();

    if (need_statusbar_horizontal_update(pww_save))
	update_statusbar_line(answer, statusbar_x);


    return started_on_word;
}
