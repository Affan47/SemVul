New(const char* pFileName)
{
  this->file_name = (imBinMemoryFileName*)pFileName;

  SetByteOrder(imBinCPUByteOrder());
  this->IsNew = 1;

  assert(this->file_name->size);

  this->Buffer = this->file_name->buffer;
  this->BufferSize = this->file_name->size;
  this->Reallocate = this->file_name->reallocate;
  this->CurrentSize = 0;

  if (!this->Buffer)
  {
    this->Buffer = (unsigned char*)malloc(this->BufferSize);
    this->file_name->buffer = this->Buffer;
  }

  this->CurPos = this->Buffer;
  this->Error = 0;
}
