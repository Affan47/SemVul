GetHandlePosition(int handle)
{
  if ( handle < 0 || handle >= this->NumberOfHandles ){ return NULL; }
  return this->HandleGeometry[handle]->GetCenter();
}
