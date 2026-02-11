errorMessageFname(QString fname, int lineno, QString msg, int level)
{
  QFileInfo info(fname);
  if (info.exists())
    {
      QLuaEditor *e = QLuaIde::instance()->editor(fname);
      e->widget()->showLine(lineno);
      if (level)
        msg = QLuaIde::Private::tr("Error: called from here.");
      else
        msg = QLuaIde::Private::tr("Error: ") + msg;
      e->showStatusMessage(msg);
      return true;
    }
  return false;
}
