panel_beautify_info_number(buf, number, width, numfiles)
    char *buf;
    off64_t number;
    int width;
    int numfiles;
{
    char shortnumbuf[LONGEST_HUMAN_READABLE+1];
    char *shortnum;
    char longnumbuf[LONGEST_HUMAN_READABLE+1];
    char filesbuf[LONGEST_HUMAN_READABLE+1];
    char *filestr;
    int scaled;

    filestr=panel_beautify_number(filesbuf, (off64_t) numfiles,
				  (GroupDigits ? human_group_digits : 0));


#define STATIC_TEXT_LEN 18
    scaled=panel_fit_number(longnumbuf, number, 0,
			    (width - (STATIC_TEXT_LEN + strlen(filestr))));
    if ( (!scaled) && (number > 999) )
    {
	shortnum=panel_beautify_number(shortnumbuf, number,
				       (human_SI|human_autoscale|human_base_1024));
	sprintf(buf, "%s (%sB) in %s file%s", longnumbuf, shortnum,
		filestr, (numfiles > 1) ? "s" : "");
    }
    else
    {
	sprintf(buf, "%s in %s file%s", longnumbuf, filestr, (numfiles > 1) ? "s" : "");
    }
    return buf;
}
