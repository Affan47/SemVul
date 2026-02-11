getValueProperty(ExecState *, int token) const
{


  switch (token) {
  case Length:
  {
    if ( !part )
      return jsNumber( 0 );

    KParts::BrowserExtension *ext = part->browserExtension();
    if ( !ext )
      return jsNumber( 0 );

    KParts::BrowserInterface *iface = ext->browserInterface();
    if ( !iface )
      return jsNumber( 0 );

    QVariant length = iface->property( "historyLength" );

    if ( length.type() != QVariant::UInt )
      return jsNumber( 0 );

    return jsNumber( length.toUInt() );
  }
  default:
    kDebug(6070) << "WARNING: Unhandled token in History::getValueProperty : " << token;
    return jsUndefined();
  }
}
