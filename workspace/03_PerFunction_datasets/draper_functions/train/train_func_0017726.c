buttonRelease(const XEvent *pXEvent_)
{
  if (isProtected()==MSFalse)
   {
     if (pXEvent_->xbutton.button==Button1||pXEvent_->xbutton.button==Button2) release();
   }
}
