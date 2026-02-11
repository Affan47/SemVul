CreateImageIO(const char *path, FileModeType mode)
{
  std::list< ImageIOBase::Pointer > possibleImageIO;
  std::list< LightObject::Pointer > allobjects =
    ObjectFactoryBase::CreateAllInstance("itkImageIOBase");

  MutexLockHolder<SimpleFastMutexLock> mutexHolder(createImageIOLock);

  for ( std::list< LightObject::Pointer >::iterator i = allobjects.begin();
        i != allobjects.end(); ++i )
    {
    ImageIOBase *io = dynamic_cast< ImageIOBase * >( i->GetPointer() );
    if ( io )
      {
      possibleImageIO.push_back(io);
      }
    else
      {
      std::cerr << "Error ImageIO factory did not return an ImageIOBase: "
                << ( *i )->GetNameOfClass()
                << std::endl;
      }
    }
  for ( std::list< ImageIOBase::Pointer >::iterator k = possibleImageIO.begin();
        k != possibleImageIO.end(); ++k )
    {
    if ( mode == ReadMode )
      {
      if ( ( *k )->CanReadFile(path) )
        {
        return *k;
        }
      }
    else if ( mode == WriteMode )
      {
      if ( ( *k )->CanWriteFile(path) )
        {
        return *k;
        }
      }
    }
  return ITK_NULLPTR;
}
