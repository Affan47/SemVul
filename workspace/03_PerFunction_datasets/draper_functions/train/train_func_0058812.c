GDSearch(GopherDirObj *gd, char *text)
{
     int       i;
     GopherObj *gs;
     int       cplen;
     char      *cp;

     Debug("GDSearch: %s;\n",text);

     if (gd == NULL)
	  return(-1);

     if (text == NULL)
	  return(-1);

     if ((int) strlen(text) <= 1)
	  return(-1);

     for (i=0; i< GDgetNumitems(gd); i++) {

	  gs = GDgetEntry(gd, i);
	  cp = GSgetPath(gs);
	  if (cp != NULL) {
	       cplen = strlen(cp);

	       if (cplen >1 && strcmp(text+1, cp+1) == 0) {
		    Debugmsg("Matched\n");
		    return(i);
	       }
	  }
     }
     Debugmsg("GDsearch: No Match\n");
     return(-1);
}
