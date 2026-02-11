GetTranslation(vtkEvent *VTKEvent)
{
  EventMapIterator iter = this->EventMap->find(VTKEvent->GetEventId());
  if ( iter != this->EventMap->end() )
    {
    EventList &elist = (*iter).second;
    return elist.find(VTKEvent);
    }
  else
    {
    return vtkWidgetEvent::NoEvent;
    }
}
