RenderOpaqueGeometry(
  vtkViewport *viewport)
{


  this->BuildRepresentation();

  GLboolean flag = GL_FALSE;
  if ( this->AlwaysOnTop
      && (this->ActiveActor->GetVisibility() ||
          this->LinesActor->GetVisibility()))
    {
    glGetBooleanv(GL_DEPTH_TEST,&flag);
    if(flag)
      {
      glDisable( GL_DEPTH_TEST );
      }
    }

  int count=0;
  count += this->LinesActor->RenderOpaqueGeometry(viewport);
  if ( this->Actor->GetVisibility() )
    {
    count += this->Actor->RenderOpaqueGeometry(viewport);
    }
  if ( this->ActiveActor->GetVisibility() )
    {
    count += this->ActiveActor->RenderOpaqueGeometry(viewport);
    }
  if(this->ShowSelectedNodes && this->SelectedNodesActor &&
      this->SelectedNodesActor->GetVisibility())
    {
    count += this->SelectedNodesActor->RenderOpaqueGeometry(viewport);
    }

  if(flag && this->AlwaysOnTop
          && (this->ActiveActor->GetVisibility() ||
              this->LinesActor->GetVisibility()))
    {
    glEnable( GL_DEPTH_TEST );
    }

  return count;
}
