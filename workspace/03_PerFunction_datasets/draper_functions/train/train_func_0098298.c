mcxStrRChrAint
(  const char*    p
,  int          (*fbool)(int c)
,  ofs            offset
)
   {  const char* z  =  offset >= 0 ? p+offset : p + strlen(p)
   ;  while (--z >= p && fbool((unsigned char) *z))
      ;
      return (char*) (z >= p ? z : NULL)
;  }
