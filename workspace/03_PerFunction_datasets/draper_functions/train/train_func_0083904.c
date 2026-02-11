moveCursorY(int y_)
{
  clearCursor();
  unsigned y=cursorY();
  if (y_<0&&firstLine()>0)
   {
     unsigned n=-y_;
     n=((firstLine()-n)>0)?n:firstLine();
     scrollDown(n);
     moveCursor(0,cursorX());
   }
  else if (y_>=0)
   {
     if (y_>=numLines())
      {
        if (line(numLines()-1)->end()<length())
	 {
           scrollUp(y_-numLines()+1);
           moveCursor((numLines()-1),cursorX());
	 }
        else server()->bell();
      }
     else if (y_>=0&&y_<numLines())
      {
        if (line(y_)->start()<length()) moveCursor(y_,cursorX());
	else server()->bell();
      }
     else server()->bell();
   }
  else server()->bell();
}
