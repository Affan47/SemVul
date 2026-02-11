open(const char * filename)
{
  if (hexEditor->open(filename)) {
    if( isTopLevel() )
      setWindowTitle(filename);
    else
      statusLabel->setText(filename);
    actions[SaveAction]->setEnabled(true);
    actions[SaveAsAction]->setEnabled(true);
    actions[UndoAction]->setEnabled(true);
    actions[RedoAction]->setEnabled(true);
    return true;
  } else {
    return false;
  }
}
