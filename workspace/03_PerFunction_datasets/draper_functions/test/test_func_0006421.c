mcxStrEscapedValue
(  const char* p
,  const char* z
,  int   *value
)
   {  u8 val = p[0]
   ;  const char* q = NULL
   ;  if (val != '\\')
      {  *value = val
      ;  return (char*) (p+1)
   ;  }
      if (!(q = xtr_get_token(p, z, NULL, &val, NULL)))
      return NULL
   ;  *value = val
   ;  return (char*) q
;  }
