expand_conquer(word_t * wrd)
{
   	word_t * pcrt = wrd;
	char * scrt = malloc(1);
    int len = 1;
    scrt[0] = '\0';
    while(pcrt)
    {
    	const char * x;
    	if (pcrt->expand) {
    		x = getenv(pcrt->string);
    		if (x == NULL)
    			x = "";
    	} else {
    		x = pcrt->string;
    	}
    	len += strlen(x);
    	scrt = realloc(scrt, len);
    	strcat(scrt, x);
    	pcrt = pcrt->next_part;
 	}
 	return scrt;
}
