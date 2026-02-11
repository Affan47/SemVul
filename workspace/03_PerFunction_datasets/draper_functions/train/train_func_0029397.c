Render(vtkRenderer* renderer, vtkProp** propArray,
  int propArrayCount)
{
  if (this->Renderer != renderer)
    {
    vtkErrorMacro("Usage error.");
    return 0;
    }


  int propsRenderered = 0;


  for (int i = 0; i < propArrayCount; i++ )
    {


    if (!propArray[i]->GetPickable() || !propArray[i]->GetSupportsSelection())
      {
      continue;
      }
    this->PropID = this->GetPropID(i, propArray[i]);
    this->Internals->Props[this->PropID] = propArray[i];
    if (this->IsPropHit(this->PropID))
      {
      propsRenderered += propArray[i]->RenderOpaqueGeometry(renderer);
      }
    }


  for (int i = 0; i < propArrayCount; i++ )
    {
    if (!propArray[i]->GetPickable() || !propArray[i]->GetSupportsSelection())
      {
      continue;
      }
    this->PropID = this->GetPropID(i, propArray[i]);
    this->Internals->Props[this->PropID] = propArray[i];
    if (this->IsPropHit(this->PropID))
      {
      propsRenderered += propArray[i]->RenderOverlay(renderer);
      }
    }

  return propsRenderered;
}
