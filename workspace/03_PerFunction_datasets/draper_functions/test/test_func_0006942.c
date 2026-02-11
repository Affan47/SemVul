cfg_parse_file(char *filename)
{
    struct CFG_ENTRIES * e = NULL;
    char line[256],tag[64],value[192];
    FILE *fp;
    int nr;
    int i;

    if (NULL == c)
	c = cfg_init_sections();
    if (NULL == (fp = fopen(filename,"r")))
      {
	perror("cpu: cfg_parse_file");
	return -1;
      }

    nr = 0;
    while (NULL != fgets(line,255,fp)) {
	nr++;
	for (i=0;i<255;i++) {
	  if (line[i] == '\t')
	    line[i] = ' ';
	}
	if (line[0] == '\n' || line[0] == '#' || line[0] == '%')
	    continue;
	if (1 == sscanf(line,"[%99[^]]]", value)) {

	    e = cfg_find_section(c,value);
	} else if (2 == sscanf(line," %63[^= ] = %191[^\n]",tag,value)) {
	  if (NULL == e)
	      e = cfg_find_section(c, "");
	  i=0;
	  if (value[0] == '"') {
	    i=1;
	    while ( (value[i] != '\0') && (value[i] != '"') )
	      i++;
	    if (value[i] == '"') {
	      value[i] = '\0';
	      i=1;
	    } else
	      i=0;
	  }
	  cfg_set_entry(e, tag, &value[i]);
	} else {
	  fprintf(stderr,
	      "ERROR: %s:%d: syntax error\n", filename, nr);
	}
    }
    return 0;
}
