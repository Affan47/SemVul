WriteImageInformation(const void *buffer)
{
  this->UpdateHeaderFromImageIO();

  this->UpdateHeaderWithMinMaxMean(buffer);

  std::ofstream file;

  this->OpenFileForWriting(file, this->m_FileName.c_str(), true);


  const MRCHeaderObject::Header & header = m_MRCHeader->GetHeader();
  file.write(static_cast< const char * >( (void *)&( header ) ), 1024);
}
