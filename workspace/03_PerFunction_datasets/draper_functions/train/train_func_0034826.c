AttachToGraph(vtkGraph *graph)
{
  this->Graph = graph;


  int numProcs
    = this->Graph->GetInformation()->Get(vtkDataObject::DATA_NUMBER_OF_PIECES());
  int tmp = numProcs - 1;

  int numProcBits = 0;
  while( tmp != 0 )
    {
    tmp >>= 1;
    numProcBits++;
    }
  if (numProcs == 1)  numProcBits = 1;

  this->signBitMask = static_cast<vtkIdType>(1) << ((sizeof(vtkIdType) * CHAR_BIT) - 1);
  this->highBitShiftMask = static_cast<vtkIdType>(1) << numProcBits;
  this->procBits = numProcBits + 1;
  this->indexBits = (sizeof(vtkIdType) * CHAR_BIT) - (numProcBits + 1);
}
