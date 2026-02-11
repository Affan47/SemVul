set_contour_labelsCmd()
{
	extern bool     _contour_label_rotated;
	extern bool     _contour_label_whiteunder;
	Require(_nword == 4, NUMBER_WORDS_ERROR);
	if (word_is(3, "rotated"))
		_contour_label_rotated = true;
	else if (word_is(3, "horizontal"))
		_contour_label_rotated = false;
	else if (word_is(3, "whiteunder"))
		_contour_label_whiteunder = true;
	else if (word_is(3, "nowhiteunder"))
		_contour_label_whiteunder = false;
	else {
		err("Last word of `set contour labels' must be `rotated|horizontal|whiteunder|nowhiteunder'");
		return false;
	}
	return true;
}
