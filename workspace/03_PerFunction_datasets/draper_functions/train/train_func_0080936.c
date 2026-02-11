isgaylenocia (uaecptr addr)
{

	if (!isgayle ())
		return true;
	uaecptr mask = addr & 0xf000;
	bool cia = mask == 0xe000 || mask == 0xd000;
	return cia;
}
