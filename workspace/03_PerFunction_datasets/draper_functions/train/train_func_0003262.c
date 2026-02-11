mcxOptParseString
(  char* src
,  int*  argc
,  unsigned char delim
)
   {  dim srclen  =  strlen(src)
   ;  dim n_delim =  mcxStrCountChar(src, delim, srclen)
   ;  dim n_args  =  0
   ;  char** argv
   ;  char *z  =  src + srclen
   ;  char *p = src, *os

   ;  *argc = 0

   ;  if (!srclen)
      return NULL

   ;  if (!(argv = mcxAlloc(sizeof(char*) * (n_delim+1), RETURN_ON_FAIL)))
      return NULL

   ;  while (p<z)
      {  while ((unsigned char) p[0] == delim)
         p++
      ;  if (p>=z)
         break
      ;  os = p
      ;  if (!(p = strchr(os, delim)))
         p = z
      ;  *p = '\0'
      ;  argv[n_args++] = os
      ;  p++
   ;  }

      *argc = n_args
   ;  return argv
;  }
