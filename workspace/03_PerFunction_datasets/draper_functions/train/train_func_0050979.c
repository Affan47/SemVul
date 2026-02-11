WriteImageInformation()
{
  this->m_IsCompressed = this->IsCompressedFilename(this->m_FileName);
  this->OpenFile();
  this->WriteHeader();
  this->CloseFile();
}
