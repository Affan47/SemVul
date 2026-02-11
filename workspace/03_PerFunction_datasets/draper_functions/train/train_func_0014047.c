SetLabels(vtkStringArray *labels)
{


  int i, numLabels = labels->GetNumberOfValues();
  if (this->NumberOfLabelsBuilt != numLabels)
    {
    if (this->LabelMappers != NULL)
      {
      for (i = 0; i < this->NumberOfLabelsBuilt; i++)
        {
        this->LabelVectors[i]->Delete();
        this->LabelMappers[i]->Delete();
        this->LabelActors[i]->Delete();
        this->LabelActors2D[i]->Delete();
        }
      delete [] this->LabelVectors;
      delete [] this->LabelMappers;
      delete [] this->LabelActors;
      delete [] this->LabelActors2D;
      }

    this->LabelVectors = new vtkVectorText * [numLabels];
    this->LabelMappers = new vtkPolyDataMapper * [numLabels];
    this->LabelActors  = new vtkAxisFollower * [numLabels];
    this->LabelActors2D = new vtkTextActor * [numLabels];

    for (i = 0; i < numLabels; i++)
      {
      this->LabelVectors[i] = vtkVectorText::New();
      this->LabelMappers[i] = vtkPolyDataMapper::New();
      this->LabelMappers[i]->SetInput(this->LabelVectors[i]->GetOutput());
      this->LabelActors[i] = vtkAxisFollower::New();
      this->LabelActors[i]->SetMapper(this->LabelMappers[i]);
      this->LabelActors[i]->SetEnableDistanceLOD(0);
      this->LabelActors[i]->GetProperty()->SetAmbient(1.);
      this->LabelActors[i]->GetProperty()->SetDiffuse(0.);
      this->LabelActors[i]->GetProperty()->SetColor(this->LabelTextProperty->GetColor());
      this->LabelActors2D[i] = vtkTextActor::New();
      }
    }


  for (i = 0; i < numLabels; i++)
    {
    this->LabelVectors[i]->SetText(labels->GetValue(i).c_str());
    this->LabelActors2D[i]->SetInput(this->LabelVectors[i]->GetText());
    }
  this->NumberOfLabelsBuilt = numLabels;
  this->LabelBuildTime.Modified();
}
