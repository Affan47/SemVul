InvokeCallback(unsigned long widgetEvent)
{
  vtkCallbackMap::CallbackMapIterator iter = this->CallbackMap->find(widgetEvent);
  if ( iter != this->CallbackMap->end() )
    {
    vtkAbstractWidget *w = (*iter).second.Widget;
    CallbackType f = (*iter).second.Callback;
    (*f)(w);
    }
}
