ReleaseGraphicsResources(vtkWindow* w)
{
  if (w && w->GetMapped() && this->IsProgram())
    {
    vtkgl::DeleteProgram(this->Program);
    }
  this->Program = 0;
  this->Superclass::ReleaseGraphicsResources(w);
}
