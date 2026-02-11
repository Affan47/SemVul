subtable(unsigned offset) const throw (Bounds)
{
    if (offset > (unsigned) _str.length())
	throw Bounds();
    return Data(_str.substring(offset));
}
