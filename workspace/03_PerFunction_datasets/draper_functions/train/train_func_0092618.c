printClear(void)
{
  if (activeClip()!=0) unsetClip();
  deleteAllClipGC();
  deleteAllDashGC();
  init();
}
