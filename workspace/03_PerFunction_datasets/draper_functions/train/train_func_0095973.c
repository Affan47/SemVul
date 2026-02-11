parseHeaders(FILE* fd, u_int& lineno)
{
    fxStackBuffer buf;
    fxStr field;
    while (getLine(fd, buf)) {
	lineno++;
	if (buf.getLength() == 0)
	    break;


	fxStr line(&buf[0], buf.getLength());
	u_int len = line.length();
	while (len > 0 && isspace(line[line.length()-1])) {
	    line.remove(line.length()-1, 1);
	    len--;
	}
	if (len > 0 && !isspace(line[0])) {
	    u_int l = 0;
	    field = line.token(l, ':');
	    if (field != "" && l < len) {
		fields.append(field);

		for (; l < len && isspace(line[l]); l++)
		    ;
		headers.append(line.tail(len-l));
		if (verbose)
		    fprintf(stderr, _("HEADER %s: %s\n")
			, (const char*) fields[fields.length()-1]
			, (const char*) headers[headers.length()-1]
		    );
	    }
	} else if (field != "")  {
	    headers[headers.length()-1].append(line);
	    if (verbose)
		fprintf(stderr, _("+HEADER %s: %s\n")
		    , (const char*) field
		    , (const char*) line
		);
	}

    }


    for (u_int i = 0, n = fields.length();  i < n; i++) {
	const fxStr& field = fields[i];
	if (strncasecmp(field, "x-fax-", 6) == 0)
	    setConfigItem(&field[6], headers[i]);
    }
}
