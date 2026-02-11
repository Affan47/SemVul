CreateCellLists(int dataSetIndex, int *regionList, int listSize)
{
  vtkDataSet *dataSet = this->GetDataSet(dataSetIndex);
  if (!dataSet)
    {
    vtkErrorMacro(<<"vtkKdTree::CreateCellLists invalid data set");
    return;
    }

  this->CreateCellLists(dataSet, regionList, listSize);
  return;
}
