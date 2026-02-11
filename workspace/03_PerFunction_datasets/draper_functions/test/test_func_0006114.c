emitslatproto(FILE* fp)
{
  node* np=firstslat;
  const char* t="ick_type32";
  while(np)
  {
    fprintf(fp,"%s ick_og%lx(%s);\nvoid ick_os%lx(%s, void(*)());\n",
	    t,(unsigned long)np,t,(unsigned long)np,t);
    np=np->nextslat;
  }
}
