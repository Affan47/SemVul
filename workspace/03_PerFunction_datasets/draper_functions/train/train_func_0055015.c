protect(const QVariant &var)
{
  QMutexLocker lock(&mutex);
  int size = saved.size();
  saved.append(var);
  if (! size)
    QCoreApplication::postEvent(this, new QEvent(QEvent::User));
  return true;
}
