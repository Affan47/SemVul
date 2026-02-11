SetCamera(vtkCamera* camera)
{
  if(this->Camera) this->Camera->Delete();
  this->Camera = camera;
}
