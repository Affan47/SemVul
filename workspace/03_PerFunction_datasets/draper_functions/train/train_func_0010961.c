widget(Window window_) const
{
  MSWidget *pWidget=(MSWidget *)_server->widgetHashTable()->lookup(window_);
  return ((unsigned long)pWidget==_server->widgetHashTable()->notFound())?0:pWidget;
}
