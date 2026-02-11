button1Release(const XEvent *pEvent_)
{
  if (inputFocus()==this&&hadFocus()==MSTrue)
   {
     if (hasCallback(MSWidgetCallback::reference)==MSTrue) reference();
     else if (isProtected()==MSFalse) startEditing(pEvent_);
   }
}
