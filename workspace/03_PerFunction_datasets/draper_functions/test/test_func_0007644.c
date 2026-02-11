mc_token(char **token, char **line)
{
    int   rv = 0;
    char *start, *wsp = NULL;

    *token = NULL;


    while(**line && isspace((unsigned char) **line))
      (*line)++;

    start = *line;


    while(1)
      switch(**line){
	case ';' :
	  rv = 1;
	case '\n' :
	  if(wsp)
	    *wsp = '\0';
	  else
	    *start = '\0';

	  (*line)++;

	  if(rv == 1){
	      while(**line){
		  if(**line == '\n')
		    rv = 0;

		  if(isspace((unsigned char) **line))
		    (*line)++;
		  else
		    break;
	      }
	  }

	case '\0' :
	  return(rv);

	case '\\' :
	  (*line)++;
#if	defined(DOS) || defined(OS2)


	  if(**line && isascii(**line)
	     && (isalnum((unsigned char) **line) || strchr("_+-=~" , **line))){
	      *start++ = '\\';
	      wsp = NULL;
	      break;
	  }
	  else
#endif

	   if(**line == '\n'){
	       *start = ' ';
	       (*line)++;
	       while(isspace((unsigned char) **line))
		 (*line)++;

	       break;
	   }
	   else if(**line == '%')
	     *--(*line) = '%';


	default :
	  if(!*token)
	    *token = start;

	  *start = *(*line)++;
	  wsp    = (isspace((unsigned char) *start) && !wsp) ? start : NULL;
	  start++;
	  break;
      }
}
