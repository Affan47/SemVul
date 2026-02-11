PostRender(vtkActor* actor, vtkRenderer* renderer)
{
  if (renderer->GetSelector())
    {

    return;
    }

  if (this->ShaderProgram && this->Shading)
    {
    this->ShaderProgram->PostRender(actor, renderer);
    }
}
