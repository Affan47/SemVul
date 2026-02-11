positionToXY(unsigned pos_,unsigned& x_,unsigned &y_)
{
  unsigned offset=panner()->highlightThickness()+panner()->shadowThickness();
  if (pos_<=length())
   {
     unsigned row=positionToRow(pos_);
     y_=offset+row*textHeight();
     unsigned start=line(row)->start();
     unsigned len=pos_-start;
     char *cp=(char *)string();
     x_=offset+textWidth(cp+start,len);
   }
  else
   {
     x_=offset;
     y_=offset;
   }
}
