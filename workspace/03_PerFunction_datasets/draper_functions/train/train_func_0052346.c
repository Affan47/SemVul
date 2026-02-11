PostRender(vtkActor*, vtkRenderer*)
{
  if (!this->GetGLExtensionsLoaded())
    {
    return;
    }

  if (this->IsProgram())
    {

    vtkgl::UseProgram(0);
    }
}
