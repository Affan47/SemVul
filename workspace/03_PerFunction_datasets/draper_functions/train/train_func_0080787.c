RenderOpaqueGeometry(vtkViewport *viewport)
{
  this->BuildRepresentation();

  if ( this->FollowCamera )
    {
    return this->Follower->RenderOpaqueGeometry(viewport);
    }
  else
    {
    return this->Actor->RenderOpaqueGeometry(viewport);
    }
}
