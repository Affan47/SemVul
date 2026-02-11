addStdActionToMenu(StdAction what, QMenu *menu)
{
  QAction *action = stdAction(what);
  if (action)
    menu->addAction(action);
  return action;
}
