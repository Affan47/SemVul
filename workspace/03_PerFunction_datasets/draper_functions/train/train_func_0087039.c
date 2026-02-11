drawImage(GR_Image* pImg, UT_sint32 xDest, UT_sint32 yDest)
{
   if (pImg)
     pImg->render(this, xDest, yDest);
}
