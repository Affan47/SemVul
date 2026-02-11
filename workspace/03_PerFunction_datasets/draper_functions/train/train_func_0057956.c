findback(pattern,start,endp)

char *pattern;
int start, endp;
{
    int ep,i;

     while (start > endp) {
	 ep = bseekeol(start);
	 if ((i = REmatch(pattern, ep, start)) <= start)
	     return i;
	 start = ep-1;
     }
     return ERR;
 }
