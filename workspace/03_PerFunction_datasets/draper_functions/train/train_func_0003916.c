GetPoint( ExXML &xml )
{
  double x;
  xml.GetPropertyValue(wxT("x")).ToDouble( &x );
  double y;
  xml.GetPropertyValue(wxT("y")).ToDouble( &y );
  long int c;
  xml.GetPropertyValue(wxT("color")).ToLong( &c );
  return new GRA_point( x, y, GRA_colorControl::GetColor(static_cast<int>(c)) );
}
