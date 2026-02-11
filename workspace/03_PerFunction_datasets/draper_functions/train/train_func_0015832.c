MapScalarsThroughTable2(void *input,
                                             unsigned char *output,
                                             int inputDataType,
                                             int numberOfValues,
                                             int inputIncrement,
                                             int outputFormat)
{
  switch (inputDataType)
    {
    case VTK_BIT:
      {
      vtkIdType i, id;
      vtkBitArray *bitArray = vtkBitArray::New();
      bitArray->SetVoidArray(input,numberOfValues,1);
      vtkUnsignedCharArray *newInput = vtkUnsignedCharArray::New();
      newInput->SetNumberOfValues(numberOfValues);
      for (id=i=0; i<numberOfValues; i++, id+=inputIncrement)
        {
        newInput->SetValue(i, bitArray->GetValue(id));
        }
      vtkLookupTableMapData(this,
                            static_cast<unsigned char*>(newInput->GetPointer(0)),
                            output,numberOfValues,
                            inputIncrement,outputFormat);
      newInput->Delete();
      bitArray->Delete();
      }
      break;

    vtkTemplateMacro(
      vtkLookupTableMapData(this,static_cast<VTK_TT*>(input),output,
                            numberOfValues,inputIncrement,outputFormat)
      );
    default:
      vtkErrorMacro(<< "MapImageThroughTable: Unknown input ScalarType");
      return;
    }
}
