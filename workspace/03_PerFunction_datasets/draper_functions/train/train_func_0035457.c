shortName() const
{
    int lastIndex = 0, index;
    while ( (index=_name.indexOf("/", lastIndex)) >=0)
	lastIndex = index+1;

    return _name.mid(lastIndex);
}
