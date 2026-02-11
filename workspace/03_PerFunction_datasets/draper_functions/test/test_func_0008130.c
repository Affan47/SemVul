childCreate(MSWidget *pWidget_)
{
  if (_child==0)
   {
     _child=pWidget_;
     adjustChildPosition();
   }
}
