ep_cd(A a)
{
  A z;
  C *name;

  NDC1(a);
  name=getaname(a);
  if (name==(C *)0) ERROUT(ERR_TYPE);
  if(chdir(*name?name:getenv("HOME"))) {
#ifdef HAVE_STRERROR
    char *errstr=strerror(errno);
    z=gv(Et,2); z->p[0]=(I)gsym("error");
    z->p[1]=(I)gsv(0,(errstr)?errstr:"unknown system error");
#else
    z=gv(Et,2); z->p[0]=(I)gsym("error");
    z->p[1]=(I)gsv(0,(errno<sys_nerr)?sys_errlist[errno]:"unknown system error");
#endif
  }
  else {setPWD();z=gv(Et,1);z->p[0]=(I)gsym("ok");}
  R z;
}
