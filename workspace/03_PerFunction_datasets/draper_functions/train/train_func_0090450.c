draw_arcCmd(void)
{
	bool filled = false;
	int start_word = 2;
	if (_nword == 8) {
		if (word_is(2, "filled")) {
			filled = true;
			start_word = 3;
		} else {
			err("`draw arc' expecting `filled' but got `\\", _word[2], "'.", "\\");
			return false;
		}
	} else if (_nword != 7) {
		demonstrate_command_usage();
		NUMBER_WORDS_ERROR;
		return false;
	}
	double xc, yc, r, angle1, angle2;
	if (!getdnum(_word[start_word], &xc)) {
		READ_WORD_ERROR(".xc_cm.");
		demonstrate_command_usage(); return false;
	}
	if (!getdnum(_word[start_word + 1], &yc)) {
		READ_WORD_ERROR(".yc_cm.");
		demonstrate_command_usage();
		return false;
	}
	if (!getdnum(_word[start_word + 2], &r)) {
		READ_WORD_ERROR(".r_cm.");
		demonstrate_command_usage();
		return false;
	}
	if (!getdnum(_word[start_word + 3], &angle1)) {
		READ_WORD_ERROR(".angle_1.");
		demonstrate_command_usage();
		return false;
	}
	if (!getdnum(_word[start_word + 4], &angle2)) {
		READ_WORD_ERROR(".angle_2.");
		demonstrate_command_usage();
		return false;
	}
	gr_draw_arc_cm(filled, xc, yc, r, angle1, angle2);
	_drawingstarted = true;
	return true;
}
