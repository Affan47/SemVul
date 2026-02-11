CanReadFile(const char* fname)
{
  bool canOpen = this->Parser->OpenFile((const char*) fname);
  if (!canOpen)
    {
    vtkErrorMacro("DICOMParser couldn't open : " << fname);
    return 0;
    }
  bool canRead = this->Parser->IsDICOMFile();
  if (canRead)
    {
    return 1;
    }
  else
    {
    vtkErrorMacro("DICOMParser couldn't parse : " << fname);
    return 0;
    }
}
