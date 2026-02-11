composite ( const Image &compositeImage_,
				const Geometry &offset_,
				const CompositeOperator compose_ )
{
  modifyImage();

  ssize_t x = offset_.xOff();
  ssize_t y = offset_.yOff();
  size_t width = columns();
  size_t height = rows();

  ParseMetaGeometry (static_cast<std::string>(offset_).c_str(),
		      &x, &y,
		      &width, &height );

  CompositeImage( image(),
		  compose_,
		  compositeImage_.constImage(),
		  x, y );
  throwImageException();
}
