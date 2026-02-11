calculateHeadingsHeight(void)
{
  if (delimiterTitle().length()==0) _headingsHeight=rowHeight()/2+MSDelimiterPadding;
  else _headingsHeight=(int)(rowHeight()*1.5);
}
