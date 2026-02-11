Spin()
{
  if ( this->CurrentRenderer == NULL || this->InteractionProp == NULL )
    {
    return;
    }

  vtkRenderWindowInteractor *rwi = this->Interactor;
  vtkCamera *cam = this->CurrentRenderer->GetActiveCamera();


  double *obj_center = this->InteractionProp->GetCenter();

  double motion_vector[3];
  double view_point[3];

  if (cam->GetParallelProjection())
    {

    cam->ComputeViewPlaneNormal();
    cam->GetViewPlaneNormal( motion_vector );
    }
  else
    {

    cam->GetPosition( view_point );
    motion_vector[0] = view_point[0] - obj_center[0];
    motion_vector[1] = view_point[1] - obj_center[1];
    motion_vector[2] = view_point[2] - obj_center[2];
    vtkMath::Normalize(motion_vector);
    }

  double disp_obj_center[3];

  this->ComputeWorldToDisplay(obj_center[0], obj_center[1], obj_center[2],
                              disp_obj_center);

  double newAngle =
    vtkMath::DegreesFromRadians( atan2( rwi->GetEventPosition()[1] - disp_obj_center[1],
                                        rwi->GetEventPosition()[0] - disp_obj_center[0] ) );

  double oldAngle =
    vtkMath::DegreesFromRadians( atan2( rwi->GetLastEventPosition()[1] - disp_obj_center[1],
                                        rwi->GetLastEventPosition()[0] - disp_obj_center[0] ) );

  double scale[3];
  scale[0] = scale[1] = scale[2] = 1.0;

  double **rotate = new double*[1];
  rotate[0] = new double[4];

  rotate[0][0] = newAngle - oldAngle;
  rotate[0][1] = motion_vector[0];
  rotate[0][2] = motion_vector[1];
  rotate[0][3] = motion_vector[2];

  this->Prop3DTransform( this->InteractionProp,
                         obj_center,
                         1,
                         rotate,
                         scale );

  delete [] rotate[0];
  delete [] rotate;

  if ( this->AutoAdjustCameraClippingRange )
    {
    this->CurrentRenderer->ResetCameraClippingRange();
    }

  rwi->Render();
}
