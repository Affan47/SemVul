T1_GetStringWidth( int FontID, char *string,
		       int len,  long spaceoff, int kerning)
{

  int no_chars;
  int i;
  int *kern_pairs;
  int *charwidths;
  int spacewidth;
  int stringwidth;

  unsigned char *ustring;

  ustring=(unsigned char *) string;


  i=T1_CheckForFontID(FontID);
  if (i!=1){
    T1_errno=T1ERR_INVALID_FONTID;
    return(0);
  }


  if (pFontBase->pFontArray[FontID].pAFMData==NULL) {
    T1_errno=T1ERR_NO_AFM_DATA;
    return( 0);
  }


  if (len<0 || ustring == NULL){
    T1_errno=T1ERR_INVALID_PARAMETER;
    return(0);
  }
  if (len==0)
    no_chars=strlen(string);
  else
    no_chars=len;

  switch (no_chars) {
    case 0:

      stringwidth=0;
      break;

    case 1:


      stringwidth=T1_GetCharWidth(FontID,ustring[0]);
      if (ustring[0]==pFontBase->pFontArray[FontID].space_position)
        stringwidth+=spaceoff;
      break;

    default:


      kern_pairs=(int *)calloc(no_chars -1, sizeof(int));
      if (kern_pairs==NULL){
        T1_errno=T1ERR_ALLOC_MEM;
        return(0);
      }
      charwidths=(int *)calloc(no_chars, sizeof(int));
      if (charwidths==NULL){
        T1_errno=T1ERR_ALLOC_MEM;
        return(0);
      }


      if (kerning){
        for (i=0; i<no_chars -1; i++){
          kern_pairs[i]=T1_GetKerning( FontID, ustring[i], ustring[i+1]);
        }
      }


      spacewidth=T1_GetCharWidth(FontID,pFontBase->pFontArray[FontID].space_position)+spaceoff;


      for (i=0; i<no_chars; i++){
        if (ustring[i]==pFontBase->pFontArray[FontID].space_position)
          charwidths[i]=(int)spacewidth;
        else
          charwidths[i]=T1_GetCharWidth(FontID,ustring[i]);
      }


      stringwidth=0;
      for (i=0; i<no_chars-1; i++){
        stringwidth += kern_pairs[i];
      }
      for (i=0; i<no_chars; i++){
        stringwidth += charwidths[i];
      }


      free( charwidths);
      free( kern_pairs);

      break;
  }


  return( stringwidth);
}
