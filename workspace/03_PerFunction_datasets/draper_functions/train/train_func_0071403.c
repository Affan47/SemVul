findAction(const QString& data) const
{
  foreach(QAction *a, popup->actions()) {
    if (!a->data().toString().compare(data))
      return a;
  }
  return 0;
}
