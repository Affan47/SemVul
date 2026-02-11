ExecuteInformation()
{
  FILE* xyzFp;

  if ( this->CheckGeometryFile(xyzFp) != VTK_OK)
    {
    return;
    }

  this->CalculateFileSize(xyzFp);
  this->ReadGeometryHeader(xyzFp);

  fclose(xyzFp);
}
