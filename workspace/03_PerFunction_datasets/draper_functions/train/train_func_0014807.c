SkipByteCount(FILE* fp)
{
  if (this->BinaryFile && this->HasByteCount)
    {
    int tmp;
    if (fread(&tmp, sizeof(int), 1, fp) != 1)
      {
      vtkErrorMacro ("MultiBlockPLOT3DReader error reading file: " << this->XYZFileName
                     << " Premature EOF while reading skipping byte count.");
      fclose (fp);
      return;
      }
    }
}
