parse_integers(char* string,int args[],int margs) {
  char* cp = string;
  char* np;
  int n=0;
  if((*cp)==0) return n;
  for(;;) {
    np=cp; cp=strchr(np,',');
    if(cp!=NULL) { (*cp)=0; cp++; };
    if(n<margs) args[n]=atoi(np);
    n++;
    if(cp==NULL) break;
  };
  return n;
}
