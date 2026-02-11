dragEnterEvent(QDragEnterEvent* e)
{
  if(!(this->CurrentState == ReadyConfigure ||
     this->CurrentState == ReadyGenerate))
    {
    e->ignore();
    return;
    }

  const QMimeData* dat = e->mimeData();
  QList<QUrl> urls = dat->urls();
  QString file = urls.count() ? urls[0].toLocalFile() : QString();
  if(!file.isEmpty() &&
    (file.endsWith("CMakeCache.txt", Qt::CaseInsensitive) ||
    file.endsWith("CMakeLists.txt", Qt::CaseInsensitive) ) )
    {
    e->accept();
    }
  else
    {
    e->ignore();
    }
}
