find_left(char c, int start) const
{
    if (start < 0)
	start = 0;
    for (int i = start; i < _length; i++)
	if (_data[i] == c)
	    return i;
    return -1;
}
