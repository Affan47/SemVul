AllocateLabels(int numLabels)
{
  if (numLabels > this->NumberOfLabelsAllocated)
    {
    int i;

    delete [] this->LabelPositions;
    this->LabelPositions = 0;
    for (i=0; i < this->NumberOfLabelsAllocated; i++)
      {
      this->TextMappers[i]->Delete();
      }
    delete [] this->TextMappers;
    this->TextMappers = 0;

    this->NumberOfLabelsAllocated = numLabels;


    this->LabelPositions = new double[this->NumberOfLabelsAllocated*3];
    this->TextMappers = new vtkTextMapper * [this->NumberOfLabelsAllocated];
    for (i=0; i<this->NumberOfLabelsAllocated; i++)
      {
      this->TextMappers[i] = vtkTextMapper::New();
      this->LabelPositions[3*i] = 0;
      this->LabelPositions[3*i+1] = 0;
      this->LabelPositions[3*i+2] = 0;
      }
    }
}
