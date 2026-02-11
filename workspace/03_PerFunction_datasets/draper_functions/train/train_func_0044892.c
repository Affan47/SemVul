Render(vtkRenderer* renderer, vtkActor* actor,
                               unsigned long typeflags, bool forceCompileOnly)
{
  if (this->ChainBuildTime < this->MTime)
    {
    this->BuildPainterChain();
    this->ChainBuildTime.Modified();
    }
  this->Superclass::Render(renderer, actor, typeflags,forceCompileOnly);
}
