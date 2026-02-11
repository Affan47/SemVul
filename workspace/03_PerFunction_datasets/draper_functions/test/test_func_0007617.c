doOpenFile(QString fname)
{
  QLuaEditor *e =  QLuaIde::instance()->editor(fname);
  if (e)
    e->updateActionsLater();
}
