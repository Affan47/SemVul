lastLine(void)
{
  if (numLines()>0)
   {
     unsigned result=numLines()-1;
     Line *pline=line(result);
     while (result>0&&pline->start()>=length()) pline=line(--result);
     return result;
   }
  return 0;
}
