SetParameterValue(const char* name, string value)
{
    string parameter_name(name);
    map<string,Parameter>::iterator it;
    transform(parameter_name.begin(), parameter_name.end(),
	      parameter_name.begin(), (int(*)(int)) toupper);
    it = parameter_map.find(parameter_name);
    if (it == parameter_map.end())
    {
	string s = "The parameter '" + parameter_name +
	    "' has not been registered.";
	throw s;
    }
    (it->second).value = value;
}
