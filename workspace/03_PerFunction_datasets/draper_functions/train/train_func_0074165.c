GetSOName()
{
  if(this->Valid() &&
     this->Internal->GetFileType() == cmELF::FileTypeSharedLibrary)
    {
    return this->Internal->GetSOName();
    }
  else
    {
    return 0;
    }
}
