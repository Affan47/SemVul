dyio_ttyq (ioid id)


{ filblk_struct *filblk ;
  const char *rtnnme = "dyio_ttyq" ;

  extern int isatty(int fildes) ;


  if (INVALID_STREAMID(id))
  { errmsg(5,rtnnme,"stream id",id) ;
    return (FALSE) ; }
  filblk = &filblks[id] ;
  if (flgon(filblk->modes,io_active) == FALSE)
  { errmsg(15,rtnnme,id) ;
    return (FALSE) ; }


  if (isatty(fileno(filblk->stream)) == 1)
    return (TRUE) ;
  else
    return (FALSE) ; }
