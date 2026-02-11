operator<<( std::ostream &out, GRA_font const &font )
{
  return out << "<font info=\"" << font.wxfont_.GetNativeFontInfoDesc().mb_str(wxConvUTF8) << "\"/>\n";
}
