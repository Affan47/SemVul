fmtLatLng(const LatLng &l) {
  return  QString("%1, %3").arg(l.lat(), 0, 'f', 5) .arg(l.lng(), 0, 'f', 5);
}
