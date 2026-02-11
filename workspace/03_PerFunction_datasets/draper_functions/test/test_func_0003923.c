pico_is_good_color(char *s)
{
    struct color_table *ct;
    struct color_name_list *nl;
    int done;

    if(!s || !color_tbl)
      return(FALSE);

    if(!strcmp(s, END_PSEUDO_REVERSE))
      return(TRUE);
    else if(!struncmp(s, MATCH_NORM_COLOR, RGBLEN) || !struncmp(s, MATCH_NONE_COLOR, RGBLEN))
      return(TRUE);
    else if(*s == ' ' || isdigit(*s)){

	for(ct = color_tbl; ct->rgb; ct++)
	  if(!strncmp(ct->rgb, s, RGBLEN))
	    break;


	if(!ct->rgb){
	    int r = -1, g = -1, b = -1;
	    char *p, *comma, scopy[RGBLEN+1];

	    strncpy(scopy, s, sizeof(scopy));
	    scopy[sizeof(scopy)-1] = '\0';

	    p = scopy;
	    comma = strchr(p, ',');
	    if(comma){
	      *comma = '\0';
	      r = atoi(p);
	      p = comma+1;
	      if(r >= 0 && r <= 255 && *p){
		comma = strchr(p, ',');
		if(comma){
		  *comma = '\0';
		  g = atoi(p);
		  p = comma+1;
		  if(g >= 0 && g <= 255 && *p){
		    b = atoi(p);
		  }
		}
	      }
	    }

	    if(r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
	      ct = color_tbl;
	}
    }
    else{
	for(done=0, ct = color_tbl; !done && ct->names; ct++){
	  for(nl = ct->names; !done && nl; nl = nl->next)
	    if(nl->name && !struncmp(nl->name, s, nl->namelen))
	      done++;

	  if(done)
	    break;
	}
    }

    return(ct->names ? TRUE : FALSE);
}
