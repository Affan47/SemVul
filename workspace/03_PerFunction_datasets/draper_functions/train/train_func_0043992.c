rstrchr(char* str, char ch) {

 char *p;
 if (str==NULL) return NULL;
 p=str+strlen(str)-1;
 while (p>=str) {
    if (*p==ch) return p;
    p--;
    }
 return NULL;
 }
