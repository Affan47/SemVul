doCut()
{
  if (d->e->hasFocus())
    d->e->cut();
  updateActionsLater();
}
