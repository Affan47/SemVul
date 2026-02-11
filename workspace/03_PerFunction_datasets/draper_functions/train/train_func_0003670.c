saveAs(const QString & name)
{
  QFile f(name);
  if (!f.open( QIODevice::WriteOnly ) )
      return false;

  QFileInfo gameBoard(m_gameboardFile);
  QDataStream out(&f);
  out.setVersion(QDataStream::Qt_4_5);
  out << QString::fromLatin1(saveGameText);
  out << gameBoard.fileName();
  foreach(QGraphicsItem *item, scene()->items())
  {
    ToDraw *currentObject = qgraphicsitem_cast<ToDraw *>(item);
    if (currentObject != NULL) currentObject->save(out);
  }

  return (f.error() == QFile::NoError);
}
