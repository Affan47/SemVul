set_test_mode(fc_type fc)
{
  char *errstr;

  log_in=readopen(fc,fLOG,&errstr);

  if (make_test) {
    if (errstr==NULL)
      fatal("Log file already exists.");
    log_out=writeopen(fc,fLOG,NULL,&errstr);
    if (errstr!=NULL)
      fatal("Couldn't create log file.");
    logflag=1;
    return;
  }

  logdelay=0;
  if (errstr!=NULL)
    fatal("Couldn't open log file.");
  logflag=2;

  script_on=1;
  scriptfile=writeopen(fc,fSCR,NULL,&errstr);
  if (errstr!=NULL)
    fatal("Couldn't open script file.");
}
