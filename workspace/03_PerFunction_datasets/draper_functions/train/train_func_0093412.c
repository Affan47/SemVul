ReleaseGraphicsResources(vtkWindow *w)
{
  assert("pre: w_exists" && w!=0);
  if(this->OpaquePass!=0)
    {
    this->OpaquePass->ReleaseGraphicsResources(w);
    }

  if(this->CompositeZPass!=0)
    {
    this->CompositeZPass->ReleaseGraphicsResources(w);
    }

  if(this->FrameBufferObject!=0)
    {
    this->FrameBufferObject->Delete();
    this->FrameBufferObject=0;
    }

  if(this->ShadowMaps!=0)
    {
    delete this->ShadowMaps;
    this->ShadowMaps=0;
    }

  if(this->LightCameras!=0)
    {
    delete this->LightCameras;
    this->LightCameras=0;
    }
}
