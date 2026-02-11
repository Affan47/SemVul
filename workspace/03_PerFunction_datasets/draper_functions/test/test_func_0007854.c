buttonPress(const XEvent *pEvent_)
{
  if (isProtected()==MSFalse)
   {
     if (pEvent_->xbutton.x>=fieldValue()->x()&&
	 pEvent_->xbutton.x<=fieldValue()->x()+fieldValue()->width()&&
         pEvent_->xbutton.y>=fieldValue()->y()&&
	 pEvent_->xbutton.y<=fieldValue()->y()+fieldValue()->height())
      {
        if (acceptFocus()==MSFalse||traverseFocus(this)==MSTrue)
         {
           showMenu(pEvent_->xbutton.time);
         }
      }
   }
}
