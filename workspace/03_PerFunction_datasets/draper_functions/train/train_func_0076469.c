operator<<( std::ostream &out, GRA_boolCharacteristic const &c )
{
  if( c.isAVector_ )
  {
    std::size_t size = c.values_.size();
    out << "<characteristic name=\"" << c.name_.mb_str(wxConvUTF8) << "\""
        << " type=\"BOOL\" shape=\"VECTOR\">\n"
        << "<data size=\"" << size << "\">";
    for( std::size_t i=0; i<size-1; ++i )c.values_[i] ? out<<"1 " : out<<"0 ";
    c.values_[size-1] ? out<<'1' : out<<'0';
    out << "</data>\n</characteristic>\n";
  }
  else
  {
    if( c.value_ != c.default_ )
    {
      out << "<characteristic name=\"" << c.name_.mb_str(wxConvUTF8) << "\""
          << " type=\"BOOL\" shape=\"SCALAR\" value=\"";
      c.value_ ? out<<'1' : out<<'0';
      out << "\"/>\n";
    }
  }
  return out;
}
