clipMask ( const Magick::Image & clipMask_ )
{
  modifyImage();

  if( clipMask_.isValid() )
    {

      SetImageClipMask( image(), clipMask_.constImage() );
    }
  else
    {

      SetImageClipMask( image(), 0 );
    }
}
