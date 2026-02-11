addStdEditMenu(QMenuBar *menubar)
{
  if (!d->editMenu)
    {
      QMenu *menu = new QMenu(tr("&Edit", "edit|"), this);
      addStdActionToMenu(ActionEditCut, menu)->setEnabled(false);
      addStdActionToMenu(ActionEditCopy, menu)->setEnabled(false);
      addStdActionToMenu(ActionEditPaste, menu)->setEnabled(false);
      menu->addSeparator();
      addStdActionToMenu(ActionPreferences, menu);
      d->editMenu = menu;
    }
  if (d->editMenu)
    return menubar->addMenu(d->editMenu);
  return 0;
}
