orderboxvaluechanged(int)
{
  int j;

  for(j=0; j<10; j++)  qApp->processEvents();

  update_filter();
}
