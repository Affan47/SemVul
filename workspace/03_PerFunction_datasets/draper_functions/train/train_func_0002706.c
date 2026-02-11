SetResliceParameters( double outputSpacingX, double outputSpacingY,
    int extentX, int extentY )
{
  vtkImageReslice *reslice = vtkImageReslice::SafeDownCast(this->Reslice);

  if (reslice)
    {

    double range[2];
    vtkImageData::SafeDownCast(reslice->GetInput())->
      GetScalarRange( range );
    reslice->SetBackgroundLevel(range[0]);

    this->ColorMap->SetInput(reslice->GetOutput());
    reslice->TransformInputSamplingOff();
    reslice->AutoCropOutputOn();
    reslice->SetResliceAxes(this->ResliceAxes);
    reslice->SetOutputSpacing(outputSpacingX, outputSpacingY, 1);
    reslice->SetOutputOrigin(0.5*outputSpacingX, 0.5*outputSpacingY, 0);
    reslice->SetOutputExtent(0, extentX-1, 0, extentY-1, 0, 0);
    }
}
