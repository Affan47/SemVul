serialized() const
{
  QVariantList list;
  foreach ( const Action &action, d->mActions ) {
    QVariantMap map;
    map.insert( QString::number( action.type() ), action.value() );

    list << QVariant( map );
  }

  QByteArray data;
  QDataStream stream( &data, QIODevice::WriteOnly );
  stream.setVersion( QDataStream::Qt_4_6 );
  stream << list;

  return data;
}
