T1_GetAllCharNames( int FontID)
{
  static char **bufmem=NULL;
  register char *namedest;
  psdict *pCharStrings;
  int len, i, j;
  long nameoffset;

  int bufmemsize=0;


  if (T1_CheckForFontID(FontID)!=1){
    T1_errno=T1ERR_INVALID_FONTID;
    return( NULL);
  }

  pCharStrings=pFontBase->pFontArray[FontID].pType1Data->CharStringsP;


  len=pCharStrings[0].key.len;


  for ( i=1; i<=len; i++){

    if ((j=pCharStrings[i].key.len)){
      bufmemsize += j + 1;
    }
    else{
      len--;
      i--;
    }
  }

  nameoffset=(len+1)*sizeof( char *);
  bufmemsize += nameoffset;


  if (bufmem!=NULL)
    free(bufmem);
  if ((bufmem=(char **)malloc( bufmemsize))==NULL){
    T1_errno=T1ERR_ALLOC_MEM;
    return(NULL);
  }

  namedest=(char *)((long)bufmem + nameoffset);
  j=0;
  for ( i=0; i<len; i++){
    bufmem[i]=&(namedest[j]);
    strncpy( &(namedest[j]), pCharStrings[i+1].key.data.nameP,
	     pCharStrings[i+1].key.len);
    j += pCharStrings[i+1].key.len;
    namedest[j++]='\0';
  }
  bufmem[i++]=NULL;

  return( bufmem);

}
