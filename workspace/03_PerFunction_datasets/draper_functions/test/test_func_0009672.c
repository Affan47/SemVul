fileSave()
{
  if(_filename.isEmpty())
  {
    fileSaveAs();
    if(_filename.isEmpty())
      return;
  }
  sMapChanged(_map->currentIndex());

  QDomDocument doc = QDomDocument("openCSVAtlasDef");
  doc.appendChild(_atlas->createElement(doc));

  QFile file(_filename);
  if(file.open(QIODevice::WriteOnly))
  {
    QTextStream ts(&file);
    ts << doc.toString();
    file.close();
  }
  else
    _msghandler->message(QtWarningMsg, tr("Error Opening File"),
                         tr("<p>Could not open the file %1 for writing: %2")
                           .arg(_filename, file.errorString()),
                         QUrl::fromLocalFile(_filename), QSourceLocation());
}
