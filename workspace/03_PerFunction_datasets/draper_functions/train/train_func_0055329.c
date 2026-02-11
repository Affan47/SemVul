SetPoints(int port, vtkPoints *points)
{
  if (port < 0 || port > 1)
    {
    return;
    }
  if (this->Points[port] == points)
    {
    return;
    }
  if (this->Points[port])
    {
    this->Points[port]->Delete();
    }
  this->Points[port] = points;
  if (this->Points[port])
    {
    this->Points[port]->Register(this);
    }
  this->Modified();
}
