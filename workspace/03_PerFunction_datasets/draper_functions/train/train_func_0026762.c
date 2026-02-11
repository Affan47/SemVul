GetHandleRepresentation( int handleIndex )
{
  return (handleIndex > 7) ? NULL : this->HandleRepresentations[handleIndex];
}
