setConfigItem(const char* tag, const char* value)
{
    u_int ix;
    if (findTag(tag, (const tags*) strings, N(strings), ix)) {
	(*this).*strings[ix].p = value;
	switch (ix) {
	case 0:	setLogFacility(logFacility); break;
	}
    } else if (findTag(tag, (const tags*) numbers, N(numbers), ix)) {
	(*this).*numbers[ix].p = getNumber(value);
	switch (ix) {
	case 0: if ( (jobProtection & 0600) != 0600)
	    {
		logError("JobProtection value must include 0600, forcing");
		jobProtection |= 0600;
	    }
	}
    } else if (findTag(tag, (const tags*) booleans, N(booleans), ix)) {
	(*this).*booleans[ix].p = getBoolean(value);
    } else
	return (false);
    return (true);
}
