dyio_ioterm (void)


{ int id ;


  for (id = 4 ; id <= maxfiles ; id++)
  { if (filblks[id].dname != NULL) FREE(filblks[id].dname) ;
    if (filblks[id].fname != NULL) FREE(filblks[id].fname) ; }
  FREE(filblks) ;

  return ; }
