myfree (ptr)
    VOID * ptr;
    {
    if (hashstrings != NULL  &&  (unsigned char *) ptr >= hashstrings
      &&  (unsigned char *) ptr <= hashstrings + hashheader.stringsize)
	return;
    free (ptr);
    }
