switch_to_last_comma_first(char *incoming_fullname, char *new_full, size_t nbuf)
{
    char  save_value;
    char *save_end, *nf, *inc, *p = NULL;

    if(nbuf < 1)
      return;

    if(incoming_fullname == NULL){
	new_full[0] = '\0';
	return;
    }


    for(inc = incoming_fullname; *inc && isspace((unsigned char)*inc); inc++)
      ;


    for(p = inc + strlen(inc) - 1; *p && p >= inc &&
	  isspace((unsigned char)*p); p--)
      ;

    save_end = ++p;
    if(save_end == inc){
	new_full[0] = '\0';
	return;
    }

    save_value = *save_end;
    *save_end = '\0';
    nf = new_full;
    memset(new_full, 0, nbuf);

    if(strindex(inc, ',') != NULL){
	int add_quotes = 0;


	if(inc[0] != '"'){
	    add_quotes++;
	    if(nf-new_full < nbuf-1)
	      *nf++ = '"';
	}

	strncpy(nf, inc, MIN(nbuf - (add_quotes ? 3 : 1), nbuf-(nf-new_full)-1));
	new_full[nbuf-1] = '\0';
	if(add_quotes){
	  strncat(nf, "\"", nbuf-(nf-new_full)-1);
	  new_full[nbuf-1] = '\0';
	}
    }
    else if(strindex(inc, SPACE)){
	char *last, *end;

	end = new_full + nbuf - 1;


	last = skip_white_space(strrindex(inc, SPACE));


	for(p = last; *p && nf < end-2 && nf-new_full < nbuf; *nf++ = *p++)
	  ;

	if(nf-new_full < nbuf-1)
	  *nf++ = ',';

	if(nf-new_full < nbuf-1)
	  *nf++ = SPACE;


	for(p = inc; p < last && nf < end && nf-new_full < nbuf-1; *nf++ = *p++)
	  ;

	new_full[nbuf-1] = '\0';

	removing_trailing_white_space(new_full);
    }
    else
      strncpy(new_full, inc, nbuf-1);

    new_full[nbuf-1] = '\0';

    *save_end = save_value;
}
