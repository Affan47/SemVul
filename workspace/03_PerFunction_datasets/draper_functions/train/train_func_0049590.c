draw_boxCmd()
{
	static GriPath p(5);
	p.clear();
	double          llx, lly, urx, ury;
	if (4 == get_cmd_values(_word, _nword, "box", 4, _dstack)) {
		llx = _dstack[0];
		lly = _dstack[1];
		urx = _dstack[2];
		ury = _dstack[3];
	} else {
		demonstrate_command_usage();
		READ_WORD_ERROR("(llx, lly, urx, ury)");
		return false;
	}
	if (_nword == 6) {

		set_x_scale();
		set_y_scale();
		set_environment();
		p.push_back(llx, lly, 'm');
		p.push_back(urx, lly, 'l');
		p.push_back(urx, ury, 'l');
		p.push_back(llx, ury, 'l');
		p.push_back(llx, lly, 'l');
		p.stroke(units_user);
		return true;
	} else if (_nword == 7) {

		if (!word_is(6, "cm") && !word_is(6, "pt")) {
			demonstrate_command_usage();
			MISSING_WORD_ERROR("cm or pt");
			return false;
		}
		set_environment();
		p.push_back(llx, lly, 'm');
		p.push_back(urx, lly, 'l');
		p.push_back(urx, ury, 'l');
		p.push_back(llx, ury, 'l');
		p.push_back(llx, lly, 'l');
		if (word_is(6, "pt")) {
			p.stroke(units_pt);
		} else if (word_is(6, "cm")) {
			p.stroke(units_cm);
		} else {
			demonstrate_command_usage();
			MISSING_WORD_ERROR("cm or pt");
			return false;
		}
		return true;
	} else {
		demonstrate_command_usage();
		NUMBER_WORDS_ERROR;
		return false;
	}
}
