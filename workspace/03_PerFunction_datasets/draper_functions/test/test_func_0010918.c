getComment( unsigned int index ) throw ( out_of_range ) {
  if ( img.get() == 0 ) throw out_of_range( "check() was not called. No comments exctracted." );
  else                  return img->getComment( index );
}
