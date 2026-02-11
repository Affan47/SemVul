consume_comma(char* p)
{
    char errbuf[ANNOT_DEF_MAXLINELEN*2];

    for (; *p && isspace(*p); p++);
    if (*p != ',') {
	sprintf(errbuf,
		"',' expected, '%s' found parsing annotation definition", p);
	fatal(errbuf, EC_CONFIG);
    }
    p++;
    for (; *p && isspace(*p); p++);

    return p;
}
