makecmd(cmdline)
char *cmdline;
{ char *st, *en;
  varname vn;
  vari *va, *vs;
  int n;

  n = countfields(cmdline);
  if (lf_error) return;
  if (n==0) return;
  clcount++;


  sprintf(vn,"=clstr%d",clcount);
  vs = createvar(vn,STSYSTEM,1+strlen(cmdline),VCHAR);
  sprintf((char *)vdptr(vs),cmdline);


  sprintf(vn,"=cline%d",clcount);
  va = createvar(vn,STSYSTEM,(INT)n,VARGL);
  makefields((char *)vdptr(vs), va, n);

  if (argvalis(va,0,"for")) set_forvar(va,clcount);
  if (argvalis(va,0,"endfor")) for_level--;


  if (argvalis(va,0,"run")) run(va);

  return;
}
