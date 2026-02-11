translate (words, wrdcnt, strgs, nmbrs, flags, indxs)

char **words ;
int    wrdcnt;
char **strgs ;
int   *nmbrs ;
char  *flags ;
int   *indxs ;

  {
  int i , j;


  for (i=0 ; i<10 ; i++)
    {
    flags [i] = 0;
    indxs [i] = _error_DFN;
    }


  for (i=0 ; i<wrdcnt ; i++)
    {
    flags [i] = sscanf (words [i], "%u", &nmbrs [i]);
    for (j=0; j<MAXCMD_DFN ; j++)
      {
      if (!strcmp (strgs [j], words [i]))
        {
        indxs [i] = j;
        break;
        }
      }
    }
  return (indxs [0]);
  }
