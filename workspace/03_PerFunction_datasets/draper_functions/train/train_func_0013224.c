computeBreaks(void)
{
  MSReportTable::computeBreaks();
  if (showBreaks()==MSTrue)
   {
     updateVsb();
     redrawImmediately();
   }
}
