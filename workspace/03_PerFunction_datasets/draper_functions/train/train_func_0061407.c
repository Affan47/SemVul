setupDefault(fxStr& s, const fxStr& configured, const char* def)
{
    if (configured == "")
	s = def;
    else
	s = configured;
}
