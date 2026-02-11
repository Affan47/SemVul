GetTranslation(unsigned long VTKEvent,
                                                       int modifier, char keyCode,
                                                       int repeatCount, char* keySym)
{
  EventMapIterator iter = this->EventMap->find(VTKEvent);
  if ( iter != this->EventMap->end() )
    {
    this->Event->SetEventId(VTKEvent);
    this->Event->SetModifier(modifier);
    this->Event->SetKeyCode(keyCode);
    this->Event->SetRepeatCount(repeatCount);
    this->Event->SetKeySym(keySym);
    EventList &elist = (*iter).second;
    return elist.find(this->Event);
    }
  else
    {
    return vtkWidgetEvent::NoEvent;
    }
}
