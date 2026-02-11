shortcut(ShortcutTypes type) const {
  Q_ASSERT(type);
  if(type == DefaultShortcut)
    return property("defaultShortcut").value<QKeySequence>();

  if(shortcuts().count()) return shortcuts().value(0);
  return QKeySequence();
}
