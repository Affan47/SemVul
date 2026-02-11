Prepare(
  vtkLabelHierarchy* hier,
  vtkCamera* cam,
  double frustumPlanes[24],
  vtkRenderer* ren,
  float bucketSize[2] )
{
  this->NodesQueued = 0;
  this->SetHierarchy( hier );
  this->SetCamera( cam );
  vtkSmartPointer<vtkPlanes> frustum = vtkSmartPointer<vtkPlanes>::New();
  frustum->SetFrustumPlanes( frustumPlanes );
  this->FrustumExtractor->SetFrustum( frustum );
  for ( int i = 0; i < 2; ++ i )
    {
    this->BucketSize[i] = bucketSize[i];
    }
  this->SetRenderer( ren );
  if ( cam->GetParallelProjection() )
    {


    }
  else
    {


    double vsr;
    if ( cam->GetUseHorizontalViewAngle() )
      {
      double vs = ren->GetSize()[0];
      vsr = this->BucketSize[0] ? ( vs / this->BucketSize[0] ) : VTK_DOUBLE_MAX;
      }
    else
      {
      double vs = ren->GetSize()[1];
      vsr = this->BucketSize[1] ? ( vs / this->BucketSize[1] ) : VTK_DOUBLE_MAX;
      }
    static_cast<void>(vsr);


    }
}
