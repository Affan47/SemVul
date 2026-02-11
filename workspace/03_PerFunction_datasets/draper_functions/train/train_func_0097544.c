f77fold(Bytebuffer* lines)
{
    char* s;
    char* line0;
    char* linen;
    int linesize;
    static char trimchars[] = " \t\r\n";

    s = bbDup(lines);
    bbClear(lines);
    linesize = 0;
    line0 = s;

    while(*line0 && strchr(trimchars,*line0) != NULL) line0++;
    if(*line0 == '\0') return;
    for(;;) {
	size_t linelen;
	linen = line0;

	while(*linen != '\n' && *linen != '\0') linen++;
	if(*linen == '\0') break;
	linen++;
	linelen = (linen - line0);

	if(*line0 == '*' || linelen == 1) {
	    bbAppendn(lines,line0,linelen);
	    line0 = linen;
	    continue;
	}


	if(linelen <= (F77_MAX_STMT+1)) {
	    bbCat(lines,"      ");
	    bbAppendn(lines,line0,linelen);
	    line0 = linen;
	    continue;
	}

        bbCat(lines,"      ");
	while(linelen > F77_MAX_STMT) {
	    int incr = F77_MAX_STMT;

	    if(*(line0+(incr-1)) == '\\') incr--;
	    bbAppendn(lines,line0,incr);
	    bbCat(lines,"\n     1");
	    line0 += incr;
	    linelen -= incr;
	}

	bbAppendn(lines,line0,linelen);
	line0 = linen;
    }
}
