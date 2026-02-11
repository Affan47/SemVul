getName(uint i)
{
	Object *d = get(findByIdx(i));

	return d ? ((String*)d)->contentChar() : NULL;
}
