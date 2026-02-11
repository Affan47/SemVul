ucs4_strqchr(UCS *s, UCS ch, int *q, int m)
{
    int	 quoted = (q) ? *q : 0;

    for(; s && *s && m != 0; s++, m--){
	if(*s == '"'){
	    quoted = !quoted;
	    if(q)
	      *q = quoted;
	}

	if(!quoted && *s == ch)
	  return(s);
    }

    return(NULL);
}
