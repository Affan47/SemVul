processFunctionKey(const XEvent *pEvent_,KeySym keysym_,
					  unsigned int state_,const char *pString_)
{
  if (menuBar()!=0&&keysym_==XK_F10)
   {
     if (menuBar()->obtainFocus()==MSTrue)
      {
	menuBar()->grabAndSelect();
	return MSTrue;
      }
     return MSFalse;
   }
  else return MSShell::processFunctionKey(pEvent_,keysym_,state_,pString_);
}
