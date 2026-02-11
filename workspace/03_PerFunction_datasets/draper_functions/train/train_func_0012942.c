uplug_cleanup(void)
{
  int32_t i;

  UPlugData *pluginToRemove;

  for(i=0;i<pluginCount;i++) {
    UErrorCode subStatus = U_ZERO_ERROR;
    pluginToRemove = &pluginList[i];

    uplug_doUnloadPlug(pluginToRemove, &subStatus);
  }

  return TRUE;
}
