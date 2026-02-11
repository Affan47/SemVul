printusage()
{
    int i;

    fprintf(stdout,
	    "\nusage: wn word [-hgla] [-n#] -searchtype [-searchtype...]\n");
    fprintf(stdout, "       wn [-l]\n\n");
    fprintf(stdout, "\t-h\t\tDisplay help text before search output\n");
    fprintf(stdout, "\t-g\t\tDisplay gloss\n");
    fprintf(stdout, "\t-l\t\tDisplay license and copyright notice\n");
    fprintf(stdout, "\t-a\t\tDisplay lexicographer file information\n");
    fprintf(stdout, "\t-o\t\tDisplay synset offset\n");
    fprintf(stdout, "\t-s\t\tDisplay sense numbers in synsets\n");
    fprintf(stdout, "\t-n#\t\tSearch only sense number #\n");
    fprintf(stdout,"\nsearchtype is at least one of the following:\n");

    for (i = 1; i <= OVERVIEW; i++)
	if (searchstr[i].option)
	    fprintf(stdout, "\t%s%s\n",
		    searchstr[i].option, searchstr[i].helpstr);
}
