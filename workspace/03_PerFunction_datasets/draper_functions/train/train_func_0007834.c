openFile()
{
  kDebug() << "NotepadPart: opening " << localFilePath();
  QFile f(localFilePath());
  QString s;
  if ( f.open(QIODevice::ReadOnly) ) {
    QTextStream t( &f );
    t.setCodec( "UTF-8" );
    s = t.readAll();
    f.close();
  }
  m_edit->setPlainText(s);

  emit setStatusBarText( url().prettyUrl() );

  return true;
}
