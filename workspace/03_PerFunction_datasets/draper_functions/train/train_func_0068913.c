registerId( void )
{
   Lock lock(&_imgRef->_mutexLock);
  if( _imgRef->id() < 0 )
    {
      char id[MaxTextExtent];
      ExceptionInfo exceptionInfo;
      GetExceptionInfo( &exceptionInfo );
      _imgRef->id(_imgRef->id()+1);
      sprintf(id,"%.20g\n",(double) _imgRef->id());
      SetImageRegistry(ImageRegistryType, id, image(), &exceptionInfo);
      throwException( exceptionInfo );
  (void) DestroyExceptionInfo( &exceptionInfo );
    }
  return _imgRef->id();
}
