doLoad()
{
  QLuaTextEditMode *mode = d->e->editorMode();
  if (mode && mode->supportsLua())
    if (d->luaLoad())
      {
        QLuaIde::instance()->activateConsole(this);
        return;
      }
  showStatusMessage(tr("Unable to load file (busy)."), 5000);
  QLuaApplication::beep();
}
