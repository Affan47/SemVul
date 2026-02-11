folder_is_nick(char *nickname, FLIST *flist, int flags)
{
    register  int  i = 0;
    FOLDER_S *f;

    if(!(nickname && *nickname && flist))
      return(NULL);

    while((f = folder_entry(i, flist)) != NULL){


	if(f->nickname
	   && (!strcmp(nickname, f->nickname)
	       || (!strucmp(nickname, f->nickname)
		   && !strucmp(nickname, ps_global->inbox_name)))){
	    char source[MAILTMPLEN], *target = NULL;


	    if(!(flags & FN_WHOLE_NAME)
	       && check_for_move_mbox(f->name, source, sizeof(source), &target))
	      return(target);
	    else
	      return(f->name);
	}
	else
	  i++;
    }

    return(NULL);
}
