indcmd (bool silent)


{ lex_struct *file ;
  const char *rtnnme = "indcmd" ;


  file = dyio_scanstr(dy_cmdchn,DY_LCQS,0,'"','"') ;
  if (file->class != DY_LCQS)
  { errmsg(236,rtnnme,"file name","parameter","@") ;
    return (cmdHALTERROR) ; }


  cmdchns[level].chn = dy_cmdchn ;
  cmdchns[level].cecho = dy_cmdecho ;
  cmdchns[level].gecho = dy_gtxecho ;
  cmdchns[level].prompt = prompt ;
  dy_cmdchn = dyio_openfile(file->string,"r") ;
  if (dy_cmdchn < 0)
  { dy_cmdchn = cmdchns[level].chn ;
    return (cmdHALTERROR) ; }
  (void) dyio_setmode(dy_cmdchn,'l') ;


  dyio_outfmt(dy_logchn,dy_cmdecho," \"%s\"\n",file->string) ;
  dyio_outfmt(dy_logchn,dy_gtxecho,
	      "\tcommand source file now %s\n",file->string) ;


  level++ ;
  if (dyio_ttyq(dy_cmdchn) == TRUE || silent == FALSE)
    prompt = TRUE ;
  else
    prompt = FALSE ;
  if (dyio_ttyq(dy_cmdchn) == FALSE && silent == FALSE)
    dy_cmdecho = TRUE ;
  else
    dy_cmdecho = FALSE ;

  return (cmdOK) ; }
