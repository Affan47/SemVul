workspaceNames(void) const
{
  if (isCDERunning()==MSTrue) return _pMWMWidget->workspaceNames();
  return MSStringVector();
}
