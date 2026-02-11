list_of_checked(TA_S *head)
{
    TA_S  *p;
    int    count;
    char **list, **cur;
    ADDRESS *a;


    for(p = head, count = 0; p; p = next_sel_taline(p)){
	if(p->checked && !p->skip_it){
	    if(p->frwrded){


		if(p->fullname)
		  fs_give((void **)&p->fullname);
		if(p->fcc)
		  fs_give((void **)&p->fcc);
		if(p->comment)
		  fs_give((void **)&p->comment);
		if(p->nickname)
		  fs_give((void **)&p->nickname);

		for(a = p->addr; a; a = a->next)
		  count++;
	    }
	    else{


		if(p->addr && p->addr->host && p->addr->host[0] == '.')
		  p->skip_it = 1;
		else
		  count++;
	    }
	}
    }


    list = (char **)fs_get((count + 1) * sizeof(char *));
    memset((void *)list, 0, (count + 1) * sizeof(char *));

    cur = list;


    for(p = head; p; p = next_sel_taline(p)){
	if(p->checked && !p->skip_it){
	    if(p->frwrded)
	      for(a = p->addr; a; a = a->next){
		  ADDRESS *next_addr;
		  char    *bufp;
		  size_t   len;

		  next_addr = a->next;
		  a->next = NULL;
		  len = est_size(a);
		  bufp = (char *) fs_get(len * sizeof(char));
		  *cur++ = cpystr(addr_string(a, bufp, len));
		  a->next = next_addr;
		  fs_give((void **)&bufp);
	      }
	    else
	      *cur++ = cpystr(p->strvalue);
	}
    }

    return(list);
}
