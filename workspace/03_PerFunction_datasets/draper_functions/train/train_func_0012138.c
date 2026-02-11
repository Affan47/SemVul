catword(char *buf, SynsetPtr synptr, int wdnum, int adjmarker, int antflag)
{
    static char vs[] = " (vs. %s)";
    static char *markers[] = {
	"",
	"(predicate)",
	"(prenominal)",
	"(postnominal)",
    };


    strcpy(wdbuf, synptr->words[wdnum]);
    strcat(buf, deadjify(wdbuf));


    if (prlexid && (synptr->lexid[wdnum] != 0))
	sprintf(buf + strlen(buf), "%d", synptr->lexid[wdnum]);
    if (wnsnsflag)
	sprintf(buf + strlen(buf), "#%d", synptr->wnsns[wdnum]);


    if (getpos(synptr->pos) == ADJ) {
	if (adjmarker == PRINT_MARKER)
	    strcat(buf, markers[adj_marker]);
	if (antflag == PRINT_ANTS)
	    strcat(buf, printant(ADJ, synptr, wdnum + 1, vs, ""));
    }
}
