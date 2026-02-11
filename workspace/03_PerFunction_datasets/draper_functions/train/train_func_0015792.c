read_distinct (EnumRegistration& er, string str)
{
	vector<int>::iterator i;
	vector<string>::iterator s;


	if (str.length() > 2 && str[0] == '0' && str[1] == 'x') {
		int val = strtol (str.c_str(), (char **) 0, 16);
                return validate (er, val);
	}


	if (strspn (str.c_str(), "0123456789") == str.length()) {
		int val = strtol (str.c_str(), (char **) 0, 10);
                return validate (er, val);
        }

	for (i = er.values.begin(), s = er.names.begin(); i != er.values.end(); ++i, ++s) {
		if (str == (*s) || nocase_cmp (str, *s) == 0) {
			return (*i);
		}
	}


	map<string,string>::iterator x;

	if ((x  = hack_table.find (str)) != hack_table.end()) {

		cerr << "found hack for " << str << " = " << x->second << endl;

		str = x->second;

		for (i = er.values.begin(), s = er.names.begin(); i != er.values.end(); ++i, ++s) {
			if (str == (*s) || nocase_cmp (str, *s) == 0) {
				return (*i);
			}
		}
	}

	throw unknown_enumeration(str);
}
