Uncompress(const unsigned char* compressedData,
                              unsigned long compressedSize,
                              unsigned long uncompressedSize)
{

  vtkUnsignedCharArray* outputArray = vtkUnsignedCharArray::New();
  outputArray->SetNumberOfComponents(1);
  outputArray->SetNumberOfTuples(uncompressedSize);
  unsigned char* uncompressedData = outputArray->GetPointer(0);


  unsigned long decSize =
    this->UncompressBuffer(compressedData, compressedSize,
                           uncompressedData, uncompressedSize);


  if(!decSize)
    {
    outputArray->Delete();
    return 0;
    }


  outputArray->SetNumberOfTuples(decSize);

  return outputArray;
}
