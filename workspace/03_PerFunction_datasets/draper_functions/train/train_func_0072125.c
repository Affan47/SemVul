operator<<( std::ostream &out, GRA_stringCharacteristic const &sc )
{
  if( sc.isAVector_ )
  {
    std::size_t size = sc.values_.size();
    out << "<characteristic name=\"" << sc.name_.mb_str(wxConvUTF8)
        << "\" type=\"STRING\" shape=\"VECTOR\">\n"
        << "<data size=\"" << size << "\">";
    for( std::size_t i=0; i<size; ++i )
      out << GRA_stringCharacteristic::Encode(sc.values_[i]).mb_str(wxConvUTF8) << "\n";
    out << "</data>\n</characteristic>\n";
  }
  else
  {
    if( sc.value_ != sc.default_ )
    {
      out << "<characteristic name=\"" << sc.name_.mb_str(wxConvUTF8)
          << "\" type=\"STRING\" shape=\"SCALAR\" value=\""
          << GRA_stringCharacteristic::Encode(sc.value_).mb_str(wxConvUTF8)
          << "\"/>\n";
    }
  }
  return out;
}
