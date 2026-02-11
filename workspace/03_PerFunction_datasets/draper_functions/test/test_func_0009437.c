ReadBlock()
{
  if(_streamEndWasReached)
    return S_OK;
  while(true)
  {
    UInt32 size = (UInt32)(_bufferBase - _buffer) + _blockSize - _streamPos;
    if(size == 0)
      return S_OK;
    UInt32 numReadBytes;
    RINOK(_stream->Read(_buffer + _streamPos, size, &numReadBytes));
    if(numReadBytes == 0)
    {
      _posLimit = _streamPos;
      const Byte *pointerToPostion = _buffer + _posLimit;
      if(pointerToPostion > _pointerToLastSafePosition)
        _posLimit = (UInt32)(_pointerToLastSafePosition - _buffer);
      _streamEndWasReached = true;
      return S_OK;
    }
    _streamPos += numReadBytes;
    if(_streamPos >= _pos + _keepSizeAfter)
    {
      _posLimit = _streamPos - _keepSizeAfter;
      return S_OK;
    }
  }
}
