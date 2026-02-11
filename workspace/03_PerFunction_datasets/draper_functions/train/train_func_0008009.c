filePicture()
{
  const QString patternsString = KImageIO::pattern(KImageIO::Writing);
  QStringList patterns = patternsString.split("\n");

  if (!patterns.isEmpty()) {
      QString firstLine = patterns[0];
      patterns.removeAt(0);
      if (firstLine.contains(" *.png")) {
          firstLine.remove(" *.png");
          firstLine.prepend("*.png ");
      }
      patterns.prepend(firstLine);
  }
  const KUrl url = KFileDialog::getSaveUrl(KUrl(QString("kfiledialog:///<ktuberling>")), patterns.join("\n"), this, QString(), KFileDialog::ConfirmOverwrite);

  if( url.isEmpty() )
    return;

  KTemporaryFile tempFile;
  QString name;
  if( !url.isLocalFile() )
  {
    tempFile.open();
    name = tempFile.fileName();
  }
  else
  {
    name = url.path();
  }

  KMimeType::Ptr mime = KMimeType::findByUrl(url, 0, true, true);
  if (!KImageIO::isSupported(mime->name(), KImageIO::Writing))
  {
    KMessageBox::error(this, i18n("Unknown picture format."));
    return;
  };

  QStringList types = KImageIO::typeForMime(mime->name());
  if (types.isEmpty()) return;

  QPixmap picture(playGround->getPicture());

  if (!picture.save(name, types.at(0).toLatin1()))
  {
    KMessageBox::error
      (this, i18n("Could not save file."));
    return;
  }

  if( !url.isLocalFile() )
  {
    if (! KIO::NetAccess::upload(name, url, this))
      KMessageBox::error(this, i18n("Could not save file."));
  }

}
