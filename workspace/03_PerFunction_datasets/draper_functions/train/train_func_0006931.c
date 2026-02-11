RegReadFloat(const char* appname, const char* valname, float def_value)
{
    if (ConfigEntry* e = get_config()->Find(appname, valname))
    {
	if (e->type != ConfigEntry::Float)
	{
	    if (e->type != ConfigEntry::Binary
		|| (sscanf(e->value.c_str(), "%f", &e->f) != 1))
		return -1;
            e->type = ConfigEntry::Float;
	}
	return e->f;
    }
    RegWriteFloat(appname, valname, def_value);
    return def_value;
}
