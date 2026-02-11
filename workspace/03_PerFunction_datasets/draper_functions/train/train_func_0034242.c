CanReadBinaryFile(const char* fname)
{
  FILE* xyzFp;

  if (!fname || fname[0] == '\0')
    {
    return 0;
    }

  if ( this->CheckFile(xyzFp, fname) != VTK_OK)
    {
    return 0;
    }

  this->CalculateFileSize(xyzFp);

  int numBlocks = this->GetNumberOfBlocksInternal(xyzFp, 1);
  fclose(xyzFp);
  if (numBlocks != 0)
    {
    return 1;
    }
  return 0;
}
