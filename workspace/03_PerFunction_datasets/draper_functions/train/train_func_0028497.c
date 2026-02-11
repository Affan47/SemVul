switchparse(char *s, char *valid) {

    int i;

    while (*s) {
	if (strchr(valid,tolower(*s))==NULL) error(1,ERR_INVSW,*s);
	switch (tolower(*s)) {
	  case 'q':
	    quiet=1;
	    break;
	  case 'y':
	    yes=1;
	    break;
	  case 'f':
	    fulllist=1;
	    break;
	  case 'a':
	    useattr=1;
	    break;
	  case 't':
	    touch=1;
	    break;
	  case 'r':
	    recurse=1;
	    break;
	  case 's':
	    special=1;
	    break;
	  case 'd':
	    savedir=1;
	    break;
	  case 'e':
	    usepath=0;
	    break;
	  case 'm':
	    move=1;
	    break;
	  case '0':
	  case '1':
	  case '2':
	    for (*s-='0',i=0;i<M_UNK;++i) {
		if (metqueue[i]==*s) break;
		else if (metqueue[i]==M_UNK) {
		    metqueue[i]=*s;
		    metqueue[i+1]=M_UNK;
		    break;
		}
	    }
	    break;
	  default :
	    error(1,ERR_INVSW,NULL,*s);
	    break;
	}
	++s;
    }
    if (!quiet) banner();
}
