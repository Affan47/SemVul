quantize ( const bool measureError_  )
{
  modifyImage();

  if (measureError_)
    options()->quantizeInfo()->measure_error=MagickTrue;
  else
    options()->quantizeInfo()->measure_error=MagickFalse;

  QuantizeImage( options()->quantizeInfo(), image() );

  throwImageException();
}
