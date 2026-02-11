panTo(const LatLng &loc)
{
  evaluateJS(QString("map.panTo(new GLatLng(%1));").arg(fmtLatLng(loc)));
}
