NPP_GetValue (NPP instance, NPPVariable variable, void *value)
{
  NPError err = NPERR_NO_ERROR;
  xprintf("NPP_GetValue: variable=%d\n", variable);

  switch (variable) {
  case NPPVpluginNameString:
    *((char **)value) = "gxine starter plugin";
    break;
  case NPPVpluginDescriptionString:
    *((char **)value) =
      "will start external gxine media player for embedded media streams";
    break;
  default:
    err = NPERR_GENERIC_ERROR;
  }
  return err;
}
