PerVolumeInitialization( vtkRenderer *ren, vtkVolume *vol )
{

  vtkImageData *input = this->GetInput();
  this->PreviousScalars = this->CurrentScalars;


  if ( input == NULL )
    {
    vtkErrorMacro(<< "No Input!");
    return;
    }
  else
    {
    input->UpdateInformation();
    input->SetUpdateExtentToWholeExtent();
    input->Update();
    }

  int usingCellColors;
  this->CurrentScalars =
    this->GetScalars( input, this->ScalarMode,
                      this->ArrayAccessMode,
                      this->ArrayId,
                      this->ArrayName,
                      usingCellColors );

  if ( usingCellColors )
    {
    vtkErrorMacro("Cell Scalars not supported");
    return;
    }


  double inputSpacing[3];
  double inputOrigin[3];
  int    inputExtent[6];
  input->GetSpacing( inputSpacing );
  input->GetOrigin( inputOrigin );
  input->GetExtent( inputExtent );

  this->ComputeMatrices( inputOrigin,
                         inputSpacing,
                         inputExtent,
                         ren, vol );

  this->RenderWindow = ren->GetRenderWindow();
  this->Volume = vol;


  if ( this->LockSampleDistanceToInputSpacing )
    {

    double dist =
      (inputSpacing[0] + inputSpacing[1] + inputSpacing[2])/6.0;
    double avgNumVoxels =
      pow(static_cast<double>((inputExtent[1] - inputExtent[0]) *
                              (inputExtent[3] - inputExtent[2]) *
                              (inputExtent[5] - inputExtent[4])),
          static_cast<double>(0.333));

    if (avgNumVoxels < 100)
      {
      dist *= 0.01 + (1 - 0.01) * avgNumVoxels / 100;
      }


    if ( this->AutoAdjustSampleDistances &&
         vol->GetAllocatedRenderTime() < 1.0 )
      {
      if ( this->SampleDistance / (dist*2) < 0.999 ||
           this->SampleDistance / (dist*2) > 1.001)
        {
        this->OldSampleDistance         = dist;
        this->SampleDistance            = dist*2;
        this->InteractiveSampleDistance = dist*2;
        }
      }
    else if ( this->SampleDistance / dist < 0.999 ||
              this->SampleDistance / dist > 1.001 )
      {
      this->OldSampleDistance         = dist;
      this->SampleDistance            = dist;
      this->InteractiveSampleDistance = dist*2;
      }
    }

  this->UpdateColorTable( vol );
  this->UpdateGradients( vol );
  this->UpdateShadingTable( ren, vol );


  this->UpdateMinMaxVolume( vol );

}
