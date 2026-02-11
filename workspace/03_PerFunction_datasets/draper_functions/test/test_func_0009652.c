add(const QString &fileClass, const QString &directory)
{
   QString key = fileClass;
   QStringList result;
   KConfigGroup config = recentdirs_readList(key, result);

   result.removeAll(directory);
   result.prepend(directory);
   while(result.count() > MAX_DIR_HISTORY)
      result.removeLast();
   config.writePathEntry(key, result);
   config.sync();
}
