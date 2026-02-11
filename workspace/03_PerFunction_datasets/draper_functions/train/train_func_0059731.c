DoInvertMonochrome(std::istream &is, std::ostream &os)
{
  if ( PF.GetPixelRepresentation() )
    {
    if ( PF.GetBitsAllocated() == 8 )
      {
      uint8_t c;
      while( is.read((char*)&c,1) )
        {
        c = (uint8_t)(255 - c);
        os.write((char*)&c, 1 );
        }
      }
    else if ( PF.GetBitsAllocated() == 16 )
      {
      assert( PF.GetBitsStored() != 12 );
      uint16_t smask16 = 65535;
      uint16_t c;
      while( is.read((char*)&c,2) )
        {
        c = (uint16_t)(smask16 - c);
        os.write((char*)&c, 2);
        }
      }
    }
  else
    {
    if ( PF.GetBitsAllocated() == 8 )
      {
      uint8_t c;
      while( is.read((char*)&c,1) )
        {
        c = (uint8_t)(255 - c);
        os.write((char*)&c, 1);
        }
      }
    else if ( PF.GetBitsAllocated() == 16 )
      {
      uint16_t mask = 1;
      for (int j=0; j<PF.GetBitsStored()-1; ++j)
        {
        mask = (uint16_t)((mask << 1) + 1);
        }

      uint16_t c;
      while( is.read((char*)&c,2) )
        {
        if( c > mask )
          {


          gdcmWarningMacro( "Bogus max value: "<< c << " max should be at most: " << mask
            << " results will be truncated. Use at own risk");
          c = mask;
          }
        assert( c <= mask );
        c = (uint16_t)(mask - c);
        assert( c <= mask );
        os.write((char*)&c, 2);
        }
      }

    }
  return true;
}
