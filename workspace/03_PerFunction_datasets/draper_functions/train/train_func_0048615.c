setName(char *name)
{
	if (_name) g_free(_name);
	_name = NULL;
	if (name) _name = g_strdup(name);
}
