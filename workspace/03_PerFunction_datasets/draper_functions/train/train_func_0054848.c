compile(size_t* length, std::string& errMsg)
{
  const char *name;
  if (compile_to_file(&name, errMsg))
    return NULL;


  delete _nativeObjectFile;


  OwningPtr<MemoryBuffer> BuffPtr;
  if (error_code ec = MemoryBuffer::getFile(name, BuffPtr, -1, false)) {
    errMsg = ec.message();
    return NULL;
  }
  _nativeObjectFile = BuffPtr.take();


  sys::Path(_nativeObjectPath).eraseFromDisk();


  if ( _nativeObjectFile == NULL )
    return NULL;
  *length = _nativeObjectFile->getBufferSize();
  return _nativeObjectFile->getBufferStart();
}
