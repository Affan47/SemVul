cfg_parse_file(char *filename)
{
    struct CFG_ENTRIES *e = NULL;
    char line[256],tag[64],value[192];
    FILE *fp;
    int nr;

    if (NULL == c)
	c = cfg_init_sections();
    if (NULL == (fp = fopen(filename,"r")))
	return -1;

    nr = 0;
    while (NULL != fgets(line,255,fp)) {
	nr++;
	if (line[0] == '\n' || line[0] == '#' || line[0] == '%')
	    continue;
	if (1 == sscanf(line,"[%99[^]]]",value)) {

	    e = cfg_find_section(c,value);
	} else if (2 == sscanf(line," %63[^= ] = %191[^\n]",tag,value)) {

	    if (NULL == e) {
		fprintf(stderr,"%s:%d: error: no section\n",filename,nr);
	    } else {
		char *c = value + strlen(value)-1;
		while (c > value  &&  (*c == ' ' || *c == '\t'))
		    *(c--) = 0;
		cfg_set_entry(e,tag,value);
	    }
	} else {

	    fprintf(stderr,"%s:%d: syntax error\n",filename,nr);
	}
    }
    fclose(fp);
    return 0;
}
