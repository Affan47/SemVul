selectedString(void) const
{
  if (selectionLength()==0) return MSString();
  else return text().subString(selectionStart(),selectionLength());
}
