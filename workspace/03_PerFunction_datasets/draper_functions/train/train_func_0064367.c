optionNumOptionsCallback (SANE_Option * option, SANE_Handle handle,
                          SANE_Action action, void *value, SANE_Int * info)
{
  option = option;
  handle = handle;
  info = info;

  if (action != SANE_ACTION_GET_VALUE)
    return SANE_STATUS_INVAL;
  *(SANE_Word *) value = getNumberOfOptions ();
  return SANE_STATUS_GOOD;
}
