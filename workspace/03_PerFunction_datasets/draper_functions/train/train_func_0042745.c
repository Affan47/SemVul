OnChar()
{
  vtkRenderWindowInteractor *rwi = this->Interactor;

  switch (rwi->GetKeyCode())
    {
    case 'f' :
    case 'F' :
      {
      this->AnimState = VTKIS_ANIM_ON;
      vtkAssemblyPath *path=NULL;
      this->FindPokedRenderer(rwi->GetEventPosition()[0],
                              rwi->GetEventPosition()[1]);
      rwi->GetPicker()->Pick(rwi->GetEventPosition()[0],
                             rwi->GetEventPosition()[1], 0.0,
                             this->CurrentRenderer);
      vtkAbstractPropPicker *picker;
      if ( (picker=vtkAbstractPropPicker::SafeDownCast(rwi->GetPicker())) )
        {
        path = picker->GetPath();
        }
      if ( path != NULL )
        {
        rwi->FlyToImage(this->CurrentRenderer,picker->GetPickPosition());
        }
      this->AnimState = VTKIS_ANIM_OFF;
      break;
      }

    case 'r' :
    case 'R' :


      if (rwi->GetShiftKey() || rwi->GetControlKey())
        {
        this->Superclass::OnChar();
        }
      else if (this->HandleObservers &&
               this->HasObserver(vtkCommand::ResetWindowLevelEvent))
        {
        this->InvokeEvent(vtkCommand::ResetWindowLevelEvent, this);
        }
      else if (this->CurrentImageProperty)
        {
        vtkImageProperty *property = this->CurrentImageProperty;
        property->SetColorWindow(this->WindowLevelInitial[0]);
        property->SetColorLevel(this->WindowLevelInitial[1]);
        this->Interactor->Render();
        }
      break;

    case 'x' :
    case 'X' :
      {
      this->SetImageOrientation(this->XViewRightVector, this->XViewUpVector);
      this->Interactor->Render();
      }
      break;

    case 'y' :
    case 'Y' :
      {
      this->SetImageOrientation(this->YViewRightVector, this->YViewUpVector);
      this->Interactor->Render();
      }
      break;

    case 'z' :
    case 'Z' :
      {
      this->SetImageOrientation(this->ZViewRightVector, this->ZViewUpVector);
      this->Interactor->Render();
      }
      break;

    default:
      this->Superclass::OnChar();
      break;
    }
}
