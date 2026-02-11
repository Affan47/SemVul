ImageContour(int dim, vtkDataSet *input,
                                            vtkPolyData *output)
{
  int numContours=this->ContourValues->GetNumberOfContours();
  double *values=this->ContourValues->GetValues();
  vtkPolyData *contourOutput;

  if ( dim == 2 )
    {
    vtkMarchingSquares *msquares;
    int i;

    msquares = vtkMarchingSquares::New();
    msquares->SetInput((vtkImageData *)input);
    msquares->SetDebug(this->Debug);
    msquares->SetNumberOfContours(numContours);
    for (i=0; i < numContours; i++)
      {
      msquares->SetValue(i,values[i]);
      }

    contourOutput = msquares->GetOutput();
    msquares->Update();
    output->ShallowCopy(contourOutput);
    msquares->Delete();
    }

  else
    {
    vtkImageMarchingCubes *mcubes;
    int i;

    mcubes = vtkImageMarchingCubes::New();
    mcubes->SetInput((vtkImageData *)input);
    mcubes->SetComputeNormals (this->ComputeNormals);
    mcubes->SetComputeGradients (this->ComputeGradients);
    mcubes->SetComputeScalars (this->ComputeScalars);
    mcubes->SetDebug(this->Debug);
    mcubes->SetNumberOfContours(numContours);
    for (i=0; i < numContours; i++)
      {
      mcubes->SetValue(i,values[i]);
      }

    contourOutput = mcubes->GetOutput();
    mcubes->Update();
    output->ShallowCopy(contourOutput);
    mcubes->Delete();
    }
}
