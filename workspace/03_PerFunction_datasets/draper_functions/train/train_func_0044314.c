value_name(PermString &str) const
{
    if (_val.length() == 0 || _val[0] != '/')
	return false;
    int pos;
    for (pos = 1; pos < _val.length(); pos++)
	if (isspace((unsigned char) _val[pos]) || _val[pos] == '/')
	    return false;
    str = PermString(_val.data() + 1, pos - 1);
    return true;
}
