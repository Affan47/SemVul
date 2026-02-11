Dolly()
{
  if (this->CurrentRenderer == NULL || this->InteractionProp == NULL)
    {
    return;
    }

  vtkRenderWindowInteractor *rwi = this->Interactor;
  vtkCamera *cam = this->CurrentRenderer->GetActiveCamera();


  double view_point[3], view_focus[3];
  double motion_vector[3];

  cam->GetPosition(view_point);
  cam->GetFocalPoint(view_focus);


  double *obj_center = this->InteractionProp->GetCenter();

  double disp_obj_center[3];

  this->ComputeWorldToDisplay(obj_center[0], obj_center[1], obj_center[2],
                              disp_obj_center);

  double *center = this->CurrentRenderer->GetCenter();

  double yf = (rwi->GetEventPosition()[1] - disp_obj_center[1]) / center[1];
  double dollyFactor = pow(1.1, yf);

  dollyFactor -= 1.0;
  motion_vector[0] = (view_point[0] - view_focus[0]) * dollyFactor;
  motion_vector[1] = (view_point[1] - view_focus[1]) * dollyFactor;
  motion_vector[2] = (view_point[2] - view_focus[2]) * dollyFactor;

  if (this->InteractionProp->GetUserMatrix() != NULL)
    {
    vtkTransform *t = vtkTransform::New();
    t->PostMultiply();
    t->SetMatrix(this->InteractionProp->GetUserMatrix());
    t->Translate(motion_vector[0], motion_vector[1], motion_vector[2]);
    this->InteractionProp->GetUserMatrix()->DeepCopy(t->GetMatrix());
    t->Delete();
    }
  else
    {
    this->InteractionProp->AddPosition(motion_vector[0],
                                       motion_vector[1],
                                       motion_vector[2]);
    }

  if (this->AutoAdjustCameraClippingRange)
    {
    this->CurrentRenderer->ResetCameraClippingRange();
    }

  rwi->Render();
}
