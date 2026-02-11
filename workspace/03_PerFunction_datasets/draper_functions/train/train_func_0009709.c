OutLineInfo(FILE *file,int line,char *fileName)
#else
static void OutLineInfo(file,line,fileName)
  FILE *    file;
  int       line;
  char *    fileName;
#endif
{
    static  char * prevFileName=NULL;
    static  char * prevFileNameMS=NULL;

    char *  p;
    char *  q;

    if (! GenLineInfo) return;

    if (!GenLineInfoMS) {
	    fprintf(file, LineInfoFormatStr,line,fileName);
    } else {
      if (fileName == prevFileName) {
	    fprintf(file, LineInfoFormatStr,line,prevFileNameMS);
      } else {
        if (prevFileNameMS != NULL) free (prevFileNameMS);
        prevFileNameMS=(char *)calloc(1,strlen(fileName)+1);
        require(prevFileNameMS != NULL,"why not do this in calloc wrapper");
        q=prevFileNameMS;
        for (p=fileName; *p != 0; p++) {
            *q=*p;
            if (*q == '\\') *q='/';
            q++;
        }
      }
      prevFileName=fileName;
    };
}
