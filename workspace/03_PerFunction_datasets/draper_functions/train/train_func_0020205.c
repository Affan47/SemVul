lineToPosition(unsigned line_)
{
  unsigned offset=panner()->highlightThickness()+panner()->shadowThickness();
  int w=panner()->width()-2*offset;
  char *cp=(char *)string();
  unsigned l=0;
  int tw=0;
  unsigned len=length();
  unsigned sp=0;
  if (line_>0)
   {
     for(unsigned pos=0;pos<len;pos++)
      {
	if (cp[pos]==NewLineChar)
	 {
	   l++;
	   sp=pos+1;
	   if (l==line_) break;
	   tw=0;
	 }
	else
	 {
	   tw+=charWidth(cp[pos]);
	   if (tw>w)
	    {
	      pos--;
	      l++;
	      sp=pos+1;
	      if (l==line_) break;
	      tw=0;
	    }
	 }
      }
   }
  return sp;
}
