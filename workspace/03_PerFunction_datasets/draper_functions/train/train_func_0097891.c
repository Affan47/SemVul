historySearch()
{
  historyOverlay.clear();
  historyCursorPos.clear();
  int pos = historyPos;
  HSWidget *hsw = new HSWidget(this);
  int selected = hsw->exec(e->cursorRect().bottomRight());
  delete hsw;
  if (selected >= 0 && selected < history.size())
    pos = selected;
  toHistory(pos);
}
