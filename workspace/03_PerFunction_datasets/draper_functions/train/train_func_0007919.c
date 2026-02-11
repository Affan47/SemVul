indentAfter(int pos, int dpos)
{
  QTextBlock block = document()->findBlock(pos);
  if (block.isValid())
    {
      QString text = block.text();
      int i = pos - block.position();
      for (; i< text.size(); i++)
        if (! text[i].isSpace())
          break;
      if (i < text.size())
        return indentAt(block.position() + i);
    }
  return indentAt(pos) + dpos;
}
