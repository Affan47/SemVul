CopyCellArray(vtkIdType totalNumberOfCells,
                                                  vtkCellArray* inCells,
                                                  vtkCellArray* outCells)
{

  vtkIdType curSize = 0;
  if(outCells->GetData())
    {
    curSize = outCells->GetData()->GetNumberOfTuples();
    }
  vtkIdTypeArray* inData = inCells->GetData();
  vtkIdType newSize = curSize+inData->GetNumberOfTuples();
  vtkIdType* in = inData->GetPointer(0);
  vtkIdType* end = inData->GetPointer(inData->GetNumberOfTuples());
  vtkIdType* out = outCells->WritePointer(totalNumberOfCells, newSize);
  out += curSize;


  while(in < end)
    {
    vtkIdType length = *in++;
    *out++ = length;


    vtkIdType j;
    for(j=0;j < length; ++j)
      {
      out[j] = in[j]+this->StartPoint;
      }
    in += length;
    out += length;
    }
}
