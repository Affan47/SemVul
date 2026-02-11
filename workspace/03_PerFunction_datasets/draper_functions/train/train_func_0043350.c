updateTitle(void)
{
  AplusArray::updateTitle();
  if (mapped()==MSTrue&&frozen()==MSFalse)
   {
     drawLabel(panner()->window());
     drawHeadings(panner()->window(),firstColumn(),lastColumn());
     drawLabels(panner()->window(),firstRow(),lastRow());
   }
}
