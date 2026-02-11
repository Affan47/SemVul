ReleaseGraphicsResources()
{
  this->InitTraversal();
  vtkShader2 *s=this->GetNextShader();
  while(s!=0)
    {
    s->ReleaseGraphicsResources();
    s=this->GetNextShader();
    }
}
