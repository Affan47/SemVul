ReadInlineData(vtkXMLDataElement* element,
                                 int isAscii, void* buffer,
                                 OffsetType startWord,
                                 OffsetType numWords,
                                 int wordType)
{
  this->DataStream = this->InlineDataStream;
  this->SeekInlineDataPosition(element);
  if(isAscii)
    {
    return this->ReadAsciiData(buffer, startWord, numWords, wordType);
    }
  else
    {
    return this->ReadBinaryData(buffer, startWord, numWords, wordType);
    }
}
