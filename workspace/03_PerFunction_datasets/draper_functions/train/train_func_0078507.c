unparse(const Vector<ArchiveElement> &ar, ErrorHandler *errh)
{
    LocalErrorHandler lerrh(errh);

    StringAccum sa;
    int want_size = 8;
    sa << "!<arch>\n";
    for (const ArchiveElement *ae = ar.begin(); ae != ar.end(); ++ae) {
	if (!ae->live())
	    continue;


	const char *ndata = ae->name.data();
	int nlen = ae->name.length();
	bool must_longname = false;
	for (int i = 0; i < nlen; i++)
	    if (ndata[i] == '/') {
		lerrh.error("archive element name %<%s%> contains slash",
			    ae->name.c_str());
		nlen = i;
		break;
	    } else if (isspace((unsigned char) ndata[i]))
		must_longname = true;


	if ((nlen >= 3 && ndata[0] == '#' && ndata[1] == '1' && ndata[2] == '/')
	    || must_longname || nlen > 14) {
	    if (char *x = sa.extend(16, 1))
		sprintf(x, "#1/%-13u", (unsigned)nlen);
	    must_longname = true;
	} else
	    if (char *x = sa.extend(16, 1))
		sprintf(x, "%-16.*s", nlen, ndata);


	int wrote_size = ae->data.length() + (must_longname ? nlen : 0);
	if (char *x = sa.extend(12 + 6 + 6 + 8 + 10 + 2, 1))
	    sprintf(x, "%-12u%-6u%-6u%-8o%-10u`\n", (unsigned) ae->date,
		    (unsigned) ae->uid, (unsigned) ae->gid, (unsigned) ae->mode,
		    (unsigned) wrote_size);

	if (must_longname)
	    sa.append(ndata, nlen);
	sa << ae->data;

	want_size += 60 + wrote_size;
	if (wrote_size % 2 == 1) {

	    sa << '\n';
	    want_size++;
	}
    }


    if (want_size != sa.length()) {
	lerrh.error("out of memory");
	return String::make_out_of_memory();
    } else
	return sa.take_string();
}
