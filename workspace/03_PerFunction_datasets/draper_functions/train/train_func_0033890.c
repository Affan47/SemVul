parseDatabase(FILE* fd, FaxDBRecord* parent)
{
    FaxDBRecordPtr rec(new FaxDBRecord(parent));
    fxStr key;
    while (getToken(fd, key)) {
	if (key == "]") {
	    if (parent == 0)
		fprintf(stderr, NLS::TEXT("%s: line %d: Unmatched \"]\".\n"),
		    (const char*) filename, lineno);
	    break;
	}
	if (key == "[") {
	    parseDatabase(fd, rec);
	    continue;
	}
	fxStr value;
	if (!getToken(fd, value))
	    break;
	if (value != ":") {
	    fprintf(stderr, NLS::TEXT("%s: line %d: Missing \":\" separator.\n"),
		(const char*) filename, lineno);
	    continue;
	}
	if (!getToken(fd, value))
	    break;
	rec->set(key, value);
	if (key == nameKey)
	    add(value, rec);
    }
}
