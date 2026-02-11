GenerateOutline(void)
{
  DestroyOutline();
  UT_sint32 width = getDisplayWidth();
  UT_sint32 height = getDisplayHeight();
  UT_sint32 i,j=0;


  for(i=0; i< height;i++)
  {
    for(j =0; j< width;j++)
    {
      if(!isTransparentAt(j,i))
      {
	break;
      }
    }
    if( j < width)
    {
      GR_Image_Point * pXY = new GR_Image_Point();
      pXY->m_iX = j;
      pXY->m_iY = i;
      m_vecOutLine.addItem(pXY);
    }
  }


  for(i=0; i< height;i++)
  {
    for(j =width-1; j>= 0;j--)
    {
      if(!isTransparentAt(j,i))
      {
	break;
      }
    }
    if( j >= 0)
    {
      GR_Image_Point * pXY = new GR_Image_Point();
      pXY->m_iX = j;
      pXY->m_iY = i;
      m_vecOutLine.addItem(pXY);
    }
  }
}
