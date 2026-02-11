RequestData(vtkInformation*,
                                    vtkInformationVector** inputVector,
                                    vtkInformationVector* outputVector)
{

  vtkDataSet* input = vtkDataSet::GetData(inputVector[0]);
  vtkDataSet* output = vtkDataSet::GetData(outputVector);


  vtkIdType numPts = input->GetNumberOfPoints();
  if(numPts < 1)
    {
    vtkDebugMacro("No input!");
    return 1;
    }


  vtkSmartPointer<vtkFloatArray> newScalars =
    vtkSmartPointer<vtkFloatArray>::New();
  newScalars->SetNumberOfTuples(numPts);


  double diffVector[3] =
    { this->HighPoint[0] - this->LowPoint[0],
      this->HighPoint[1] - this->LowPoint[1],
      this->HighPoint[2] - this->LowPoint[2] };
  double length2 = vtkMath::Dot(diffVector, diffVector);
  if(length2 <= 0)
    {
    vtkErrorMacro("Bad vector, using (0,0,1).");
    diffVector[0] = 0;
    diffVector[1] = 0;
    diffVector[2] = 1;
    length2 = 1.0;
    }


  vtkIdType tenth = (numPts >= 10? numPts/10 : 1);
  double numPtsInv = 1.0/numPts;
  int abort = 0;


  double diffScalar = this->ScalarRange[1] - this->ScalarRange[0];
  vtkDebugMacro("Generating elevation scalars!");
  for(vtkIdType i=0; i < numPts && !abort; ++i)
    {

    if(i % tenth == 0)
      {
      this->UpdateProgress((i+1)*numPtsInv);
      abort = this->GetAbortExecute();
      }


    double x[3];
    input->GetPoint(i, x);
    double v[3] = { x[0] - this->LowPoint[0],
                    x[1] - this->LowPoint[1],
                    x[2] - this->LowPoint[2] };
    double s = vtkMath::Dot(v, diffVector) / length2;
    s = (s < 0.0 ? 0.0 : s > 1.0 ? 1.0 : s);


    newScalars->SetValue(i, this->ScalarRange[0] + s*diffScalar);
    }


  output->CopyStructure(input);
  output->GetPointData()->PassData(input->GetPointData());
  output->GetCellData()->PassData(input->GetCellData());


  newScalars->SetName("Elevation");
  output->GetPointData()->AddArray(newScalars);
  output->GetPointData()->SetActiveScalars("Elevation");

  return 1;
}
