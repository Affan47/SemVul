sample ( const Geometry &geometry_ )
{
  ssize_t x = 0;
  ssize_t y = 0;
  size_t width = columns();
  size_t height = rows();

  ParseMetaGeometry (static_cast<std::string>(geometry_).c_str(),
		      &x, &y,
		      &width, &height );

  ExceptionInfo exceptionInfo;
  GetExceptionInfo( &exceptionInfo );
  MagickCore::Image* newImage =
    SampleImage( image(), width, height, &exceptionInfo );
  replaceImage( newImage );
  throwException( exceptionInfo );
  (void) DestroyExceptionInfo( &exceptionInfo );
}
