parseNumber(char* &p, double& v) {

 while (*p==' ' || *p=='\t') p++;
 char* start=p;


 int numlen=strspn(start, "0123456789eE.-+");
 p=start+numlen;

 if (*start=='-' && p==start+1) return false;
 char saved=*p;
 *p='\0';
 char* endptr=p;
 v=strtod(start,&endptr);
 *p=saved;
 if (endptr!=p) return false;
 return true;
}
