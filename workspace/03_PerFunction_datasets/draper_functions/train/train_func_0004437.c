emitslat(FILE* fp)
{
  node* np=firstslat;
  node* temp, *temp2;
  const char* t="ick_type32";
  while(np)
  {
    fprintf(fp,
	    "void ick_os%lx(%s a, void(*f)())\n{\n  static int l=0;\n"
	    "  if(l)\n  {\n    if(!f) ick_lose(IE994, ick_lineno, (const char *)NULL);\n"
	    "    f(a,0);\n    return;\n  }\n  l=1;\n",
	    (unsigned long)np,t);
    temp=cons(C_A, 0, 0);
    revprexpr(np, fp, temp);
    fprintf(fp,"  l=0;\n}\n");
    fprintf(fp,"%s ick_og%lx(%s t)\n{\n  %s a;\n  static int l=0;\n"
	    "  if(l) return t;\n  l=1;\n  a=",
	    t,(unsigned long)np,t,t);
    prexpr(np, fp, 0);
    fprintf(fp,";\n  l=0;\n  return a;\n}\n");
    np=np->nextslat;
  }
  np=firstslat;


  temp2=0;
  while(np)
  {
    temp=np->nextslat;
    np->nextslat=temp2;
    temp2=np;
    np=temp;
  }
  np=temp2;
  while(np)
  {
    temp=np->nextslat;
    nodefree(np);
    np=temp;
  }

  firstslat = 0;
}
