setShortcut( const QKeySequence & keySeq, ShortcutTypes type )
{
  Q_ASSERT(type);

  if (type & DefaultShortcut)
      setProperty("defaultPrimaryShortcut", keySeq);

  if (type & ActiveShortcut) {
      QAction::setShortcut(keySeq);
  }
}
