setDeleted( const QString & _file )
{
  kDebug(7001) << objectName() << "emitting deleted" << _file;
  emit deleted( _file );
}
