set_contour_formatCmd()
{
	if (_nword < 4) {
		err("Must specify a format for `set contour format'");
		return false;
	}
	if (!strcmp(_word[3], "default")) {
		_contourFmt.assign(CONTOUR_FMT_DEFAULT);
	} else {
		if (*_word[3] == '"') {
			int len = strlen(_word[3]);
			if (len <= 1) {
				_contourFmt.assign(CONTOUR_FMT_DEFAULT);
			} else {
				if (*(_word[3] + len - 1) == '"')
					_contourFmt.assign(_word[3] + 1, len - 2);
				else
					_contourFmt.assign(_word[3] + 1, len - 1);
			}
		} else {
			_contourFmt.assign(_word[3]);
		}
	}
	return true;
}
