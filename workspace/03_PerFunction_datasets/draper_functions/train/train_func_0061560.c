resetLinePosition(unsigned line_,unsigned pos_)
{
  if (line_<numLines())
   {
     unsigned offset=panner()->highlightThickness()+panner()->shadowThickness();
     int w=panner()->width()-2*offset;
     char *cp=(char *)string();
     unsigned pos=pos_;
     unsigned len=length();
     int tw;
     unsigned i,j;
     for (i=line_;i<numLines();i++)
      {
	line(i)->start(pos);
	line(i)->dirty(MSTrue);
	tw=0;
	if (pos<len)
	 {
	   for(j=pos;j<len;j++,pos++)
	    {
	      if (cp[j]==NewLineChar) break;
              else
	       {
  	         tw+=charWidth(cp[j]);
	         if (tw>w) { pos--; break; }
	       }
	    }
	   line(i)->end(pos++);
	 }
	else line(i)->end(pos);
      }
     lineStatus();
   }
  else MSMessageLog::warningMessage("MSText::resetLinesPosition: line out of bounds");
}
