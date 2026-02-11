T1_DeleteAllSizes( int FontID)
{
  int sizecount;
  float currsize;

  FONTSIZEDEPS *ptr;

  if (T1_CheckForFontID(FontID)!=1)
    return(-1);


  sizecount=0;
  if ((ptr=T1int_GetLastFontSize( FontID))==NULL){

    return(0);
  }

  while (((ptr=T1int_GetLastFontSize(FontID)) != NULL)){
    currsize=ptr->size;
    T1_DeleteSize( FontID, currsize);
    sizecount++;

  }

  return(sizecount);
}
