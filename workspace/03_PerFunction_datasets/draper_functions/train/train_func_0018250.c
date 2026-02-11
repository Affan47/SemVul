operator<<( std::ostream &out, NumericVariable const &nv )
{
  wxString closer;
  switch ( nv.data_.GetNumberOfDimensions() )
  {
    case 0:
    {
      out << "<scalar name=\"" << nv.name_.mb_str(wxConvUTF8) << "\"";
      nv.data_.IsFixed() ? out << " type=\"FIXED\">\n" : out << " type=\"FIT\">\n";
      closer = wxT("</scalar>\n");
      break;
    }
    case 1:
    {
      out << "<vector name=\"" << nv.name_.mb_str(wxConvUTF8) << "\" size=\""
          << nv.data_.GetDimMag(0) << "\"";
      if( nv.data_.IsUnordered() )     out << " order=\"UNORDERED\">\n";
      else if( nv.data_.IsAscending() )out << " order=\"ASCENDING\">\n";
      else                             out << " order=\"DESCENDING\">\n";
      closer = wxT("</vector>\n");
      break;
    }
    case 2:
    {
      out << "<matrix name=\"" << nv.name_.mb_str(wxConvUTF8) << "\""
          << " rows=\"" << nv.data_.GetDimMag(0) << "\" columns=\""
          << nv.data_.GetDimMag(1) << "\">\n";
      closer = wxT("</matrix>\n");
      break;
    }
    case 3:
    {
      out << "<tensor name=\"" << nv.name_.mb_str(wxConvUTF8) << "\"";
      out << " rows=\"" << nv.data_.GetDimMag(0) << "\" columns=\""
          << nv.data_.GetDimMag(1) << "\" planes=\""
          << nv.data_.GetDimMag(2) << "\">\n";
      closer = wxT("</tensor>\n");
      break;
    }
  }
  out << nv.data_;
  out << "<history size=\"" << nv.history_.size() << "\">\n";
  std::deque<wxString>::const_reverse_iterator hEnd = nv.history_.rend();
  for( std::deque<wxString>::const_reverse_iterator i=nv.history_.rbegin(); i!=hEnd; ++i )
    out << "<string><![CDATA[" << (*i).mb_str(wxConvUTF8) << "]]></string>\n";
  return out << "</history>\n<origin><![CDATA[" << nv.GetOrigin().mb_str(wxConvUTF8)
             << "]]></origin>\n" << closer.mb_str(wxConvUTF8);
}
