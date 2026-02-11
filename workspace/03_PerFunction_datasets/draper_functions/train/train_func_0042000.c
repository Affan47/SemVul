AllocateOutputData(vtkPointSet *input, vtkPointSet *output)
{


  if (!output)
    {
    vtkErrorMacro("Output not created as expected!");
    return 0;
    }


  vtkPoints *points = output->GetPoints();
  if (!points)
    {
    points = vtkPoints::New();
    output->SetPoints( points );
    points->Delete();
    }
  points->SetNumberOfPoints( this->NumberOfTimeSteps );


  output->GetPointData()->CopyAllocate(input->GetPointData(), this->NumberOfTimeSteps);


  vtkDoubleArray *timeArray = vtkDoubleArray::New();
  timeArray->SetNumberOfComponents(1);
  timeArray->SetNumberOfTuples(this->NumberOfTimeSteps);
  if (input->GetPointData()->GetArray("Time"))
    {
    timeArray->SetName("TimeData");
    }
  else
    {
    timeArray->SetName("Time");
    }
  output->GetPointData()->AddArray(timeArray);
  timeArray->Delete();

  return 1;
}
