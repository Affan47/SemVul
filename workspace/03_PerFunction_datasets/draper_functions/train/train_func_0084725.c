OnLeftButtonMove()
{
  int x = this->Interactor->GetEventPosition()[0];
  int y = this->Interactor->GetEventPosition()[1];

  switch (state)
    {
    case VTK_UNICAM_CAM_INT_CHOOSE:   this->ChooseXY(x, y); break;
    case VTK_UNICAM_CAM_INT_ROT:      this->RotateXY(x, y); break;
    case VTK_UNICAM_CAM_INT_PAN:      this->PanXY(x, y); break;
    case VTK_UNICAM_CAM_INT_DOLLY:    this->DollyXY(x, y); break;
    }
}
