setBlockIndent(QTextBlock block, int indent)
{
  Q_ASSERT(block.isValid());
  int oindent;
  int cpos = getBlockIndent(block, oindent);
  if (oindent == indent)
    return cpos;
  QTextCursor cursor(block);
  cursor.setPosition(cpos, QTextCursor::KeepAnchor);
  QString spaces;
  if (!d->tabExpand && d->tabSize > 0)
    for (; indent >= d->tabSize; indent -= d->tabSize)
      spaces += '\t';
  for(; indent>=1; indent-=1)
    spaces += ' ';
  cursor.insertText(spaces);
  return cursor.position();
}
