SetCharacterData(const char* data, int length)
{

  if (length<0)
    {
    vtkWarningMacro("Negative values for length are not allowed, setting to 0!");
    length=0;
    }

  this->EndOfCharacterData=length+1;

  this->CharacterDataBufferSize=this->CharacterDataBlockSize;
  while (this->CharacterDataBufferSize<this->EndOfCharacterData)
    {
    this->CharacterDataBufferSize+=this->CharacterDataBlockSize;
    }

  this->CharacterData
    = static_cast<char *>(realloc(this->CharacterData,this->CharacterDataBufferSize));

  if (data && length>0)
    {
    memmove(this->CharacterData, data, length);
    }
  this->CharacterData[length]=0;

  this->Modified();
}
