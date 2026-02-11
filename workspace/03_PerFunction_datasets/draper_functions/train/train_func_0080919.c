icalrecur_add_bydayrules(struct icalrecur_parser *parser, const char* vals)
{

    char *t, *n;
    int i=0;
    int sign = 1;
    int weekno = 0;
    icalrecurrencetype_weekday wd;
    short *array = parser->rt.by_day;
    char* end;
    char* vals_copy;

    vals_copy = icalmemory_strdup(vals);

    end = (char*)vals_copy+strlen(vals_copy);
    n = vals_copy;

    while(n != 0){


	t = n;

	n = strchr(t,',');

	if(n != 0){
	    *n = 0;
	    n++;
	}


	if( *t == '-'){
	    sign = -1;
	    t++;
	} else if (*t == '+'){
	    sign = 1;
	    t++;
	} else {
	    sign = 1;
	}


	weekno = strtol(t,&t,10);


	if (*t == ' ')
	    t++;

	wd = icalrecur_string_to_weekday(t);

	array[i++] = (short)(sign* (wd + 8*weekno));
	array[i] =  ICAL_RECURRENCE_ARRAY_MAX;

    }

    free(vals_copy);

    sort_bydayrules(parser);
}
