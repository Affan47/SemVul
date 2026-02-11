translateStrict(const char * msgid) const
{
  QMutexLocker locker(&catalogStaticData->mutex);
  d->setupGettextEnv();
  const char *msgstr = dgettext(d->name, msgid);
  d->resetSystemLanguage();
  return msgstr != msgid ? QString::fromUtf8(msgstr) : QString();
}
