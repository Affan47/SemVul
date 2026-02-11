keyPress(const XEvent *event_, KeySym keysym_, unsigned int state_, const char *pString_)
{
  MSStringEntryField::keyPress(event_, keysym_, state_, pString_);
  if (sensitive()==MSTrue && _editor->mapped()==MSFalse)
   {


     if (isProtected()==MSTrue)
       {
	 if (keysym_==XK_Up) slot()->up();
	 else if (keysym_==XK_Down) slot()->down();
       }

     if (keysym_==XK_Tab)
      {
	unsigned int state=(state_&(ShiftMask|ControlMask|Mod1Mask));
	if (state==ShiftMask) slot()->shiftTab();
	else slot()->tab();
      }
   }
}
