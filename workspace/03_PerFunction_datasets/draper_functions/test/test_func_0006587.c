ColorLevel(
  vtkUniformGrid* input, int group)
{
  vtkUniformGrid* output = 0;
  output = input->NewInstance();
  output->ShallowCopy(input);
  vtkDataSet* dsOutput = vtkDataSet::SafeDownCast(output);
  vtkIdType numCells = dsOutput->GetNumberOfCells();
  vtkUnsignedCharArray* cArray = vtkUnsignedCharArray::New();
  cArray->SetNumberOfTuples(numCells);
  for (vtkIdType cellIdx=0; cellIdx<numCells; cellIdx++)
    {
    cArray->SetValue(cellIdx, group);
    }
  cArray->SetName("BlockIdScalars");
  dsOutput->GetCellData()->AddArray(cArray);
  cArray->Delete();
  return output;
}
