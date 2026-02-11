make_base(int size)
{
    Vector<Code> reencoding;
    for (Code c = 0; c < size && c < _encoding.size(); c++) {
	Char &ch = _encoding[c];
	if (ch.base_code >= 0 && ch.base_code != c) {
	    if (!reencoding.size())
		for (Code cc = 0; cc < _encoding.size(); cc++)
		    reencoding.push_back(cc);
	    reencoding[ch.base_code] = c;
	    reencoding[c] = ch.base_code;
	    _encoding[c].swap(_encoding[ch.base_code]);
	}
	if (ch.virtual_char)
	    ch.clear();
    }
    if (reencoding.size()) {
	reencode(reencoding);
	cut_encoding(size);
    }
    check();
}
