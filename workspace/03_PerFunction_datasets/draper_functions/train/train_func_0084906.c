mousePressEvent( QMouseEvent *e )
{
  int i = 0;
  foreach(Poppler::TextBox *tb, textRects)
  {
    if (tb->boundingBox().contains(e->pos()))
    {
      QString tt = QString("Text: \"%1\"\nIndex in text list: %2").arg(tb->text()).arg(i);
      QToolTip::showText(e->globalPos(), tt, this);
      break;
    }
    ++i;
  }
}
