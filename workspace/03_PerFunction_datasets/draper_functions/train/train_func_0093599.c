canUndo(char flag)
{
  mCanUndo = flag;

  if (!mCanUndo && undowidget==this)
    undowidget = 0;
}
