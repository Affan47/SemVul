PrintHexXML(std::ostream &os ) const
    {


    std::vector<char>::const_iterator it = Internal.begin();
    os << std::hex;
    for(; it != Internal.begin() + Length; ++it)
      {

      uint8_t v = *it;
      if( it != Internal.begin() ) os << "\\";
      os << std::setw( 2 ) << std::setfill( '0' ) << (uint16_t)v;


      }
    os << std::dec;
    }
