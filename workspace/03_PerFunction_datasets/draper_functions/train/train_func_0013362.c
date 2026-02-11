GetBuffer(char *buffer, unsigned long length) const {


    if( length <= Internal.size() )
      {
      memcpy(buffer, &Internal[0], length);
      return true;
      }
    gdcmDebugMacro( "Could not handle length= " << length );
    return false;
    }
