computeValueWinSize(void)
{
  int wmin,wmax;
  MSString buffer;
  formatValue(buffer,valueMin());
  wmin=XTextWidth(valueWin()->fontInfo(),buffer,buffer.length());
  formatValue(buffer.removeAll(),valueMax());
  wmax=XTextWidth(valueWin()->fontInfo(),buffer,buffer.length());

  formatValue(buffer.removeAll(),currentValue());
  int w=XTextWidth(valueWin()->fontInfo(),buffer,buffer.length());
  w=(w=w>wmin?w:wmin)>wmax?w:wmax;
  valueWin()->offset((slider()->width()-w)/2);
  valueWin()->resize(w,valueWin()->textHeight());
}
