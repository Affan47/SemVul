rstrstr(const char* rstart, const char *lend, const char* substr) {


 char *p;
 int l,i;
 l=strlen(substr);
 p=(char*)rstart-l+1;
 while (p>=lend) {
    for (i=0;i<l;i++) if (*(p+i) != *(substr+i)) break;
    if (i==l) return p+l-1;
    p--;
    }
 return NULL;
 }
