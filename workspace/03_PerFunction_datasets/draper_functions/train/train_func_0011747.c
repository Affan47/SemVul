cssPropertyId( const QString& p ) {
  return DOM::getPropertyID(p.toLatin1().constData(), p.length());
}
