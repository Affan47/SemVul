T1int_QueryFontSize( int FontID, float size, int aa)
{

  FONTSIZEDEPS *link_ptr;


  if (pFontBase->pFontArray[FontID].pFontSizeDeps == NULL)
    return(pFontBase->pFontArray[FontID].pFontSizeDeps);


  link_ptr=pFontBase->pFontArray[FontID].pFontSizeDeps;

  while (((link_ptr->size != size)||(link_ptr->antialias != aa))
	 &&(link_ptr->pNextFontSizeDeps != NULL))
    link_ptr=link_ptr->pNextFontSizeDeps;

  if ((link_ptr->size != size)||(link_ptr->antialias != aa))
    return( NULL);
  else
    return(link_ptr);

}
