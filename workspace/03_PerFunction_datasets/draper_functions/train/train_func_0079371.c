find_variable(const String &name, bool add)
{
    int i;
    for (i = 0; i < _vars.size(); i += 2)
	if (_vars[i] == name)
	    goto found;
    if (add) {
	_vars.push_back(name);
	_vars.push_back(String());
    }
 found:
    return i;
}
