startBlinking(void)
{
  if (isProtected()==MSFalse)
   {
     if (blinkOn()==MSFalse&&haveFocus()==MSTrue)
      {
	blinkTimer()->reset();
	_blinkOn=MSTrue;
      }
   }
}
