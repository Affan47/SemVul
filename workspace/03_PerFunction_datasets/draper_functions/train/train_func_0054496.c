button1Press(const XEvent *event_)
{
  if (event_->xbutton.state&ControlMask)
   {
     mode(Browse);
     browse();
   }
  else if (sensitive()==MSTrue)
   {
     mode(Search);
     search();
   }
  else server()->bell();
  if (mode()==Browse) repeatThreshold(MSNotebookArrowBrowseRepeatThreshold);
  else repeatThreshold(MSNotebookArrowSearchRepeatThreshold);
  if (arrowTimer()==0) _arrowTimer=new MSArrowTimer(repeatThreshold(),this);
  else arrowTimer()->expirationInterval(repeatThreshold());
  if (mode()==Browse) repeatInterval(MSNotebookArrowBrowseRepeatInterval);
  else repeatInterval(MSNotebookArrowSearchRepeatInterval);
  arrowTimer()->reset();
}
