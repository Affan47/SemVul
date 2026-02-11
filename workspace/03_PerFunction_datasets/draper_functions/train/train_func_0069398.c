updateFont(Font oldfid_)
{
  MSComposite::updateFont(oldfid_);
  if(_fieldValue->font() == oldfid_)
   {
     _fieldValue->font(font());
     XSetFont(display(),drawGC(),font());
   }
  if(oldfid_ == _fieldLabel->font()) _fieldLabel->font(font());
  if (dynamic()==MSTrue) computeSize();
  else redraw();
}
