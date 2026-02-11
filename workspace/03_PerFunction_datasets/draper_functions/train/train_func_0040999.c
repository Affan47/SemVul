sar_make_padded_number(const string & num, const infinint & min_digits)
    {
	string ret = num;

	while(infinint(ret.size()) < min_digits)
	    ret = string("0") + ret;

	return ret;
    }
