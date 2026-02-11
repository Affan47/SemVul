doBalance()
{
  QTextCursor c = e->textCursor();
  int spos = c.selectionStart();
  int epos = c.selectionEnd();
  d->parseTo(epos);
  QMap<int,Bal>::const_iterator mi = d->balances.lowerBound(epos);
  QTextBlock block = e->document()->findBlock(epos).next();
  while (mi == d->balances.end() && block.isValid())
    {
      d->parseTo(block.position());
      mi = d->balances.lowerBound(epos);
      block = block.next();
    }

  int nspos = -1;
  int nepos = epos;
  while (mi != d->balances.end() && nspos < 0)
    {
      nspos = -1;
      nepos = mi->pos + mi->len;
      while (mi != d->balances.end() && mi->pos + mi->len == nepos)
        {
          if (mi->pos < spos + (nepos > epos) ? 1 : 0)
            nspos = qMax(nspos, mi->pos);
          if (mi->outer && nspos < 0)
            return false;
          QMap<int,Bal>::const_iterator miplusone = mi; ++miplusone;
          if (miplusone == d->balances.end() && block.isValid())
            {
              d->parseTo(block.position());
              block = block.next();
              continue;
            }
          mi = miplusone;
        }
    }

  if (nspos < 0)
    return false;
  if ((nspos < spos && nepos >= epos) ||
      (nspos <= spos && nepos > epos) )
    {
      c.setPosition(nspos);
      c.setPosition(nepos, QTextCursor::KeepAnchor);
      e->setTextCursor(c);
      return true;
    }
  return false;
}
