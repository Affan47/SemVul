RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{

  vtkInformation *outInfo = outputVector->GetInformationObject(0);


  vtkPolyData *output = vtkPolyData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  FILE *fp;

  if (!this->FileName)
    {
    return 0;
    }

  if ((fp = fopen(this->FileName, "r")) == NULL)
    {
    vtkErrorMacro(<< "File " << this->FileName << " not found");
    return 0;
    }
  vtkDebugMacro(<< "opening base file " << this->FileName);
  this->ReadMolecule(fp, output);
  fclose(fp);

  output->Squeeze();

  return 1;
}
