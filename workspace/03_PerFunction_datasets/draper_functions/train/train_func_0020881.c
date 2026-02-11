init_devices (void)
{
  IDeckLinkIterator *iterator;
  IDeckLink *decklink = NULL;
  HRESULT ret;
  int i;
  static gboolean inited = FALSE;

  if (inited) return;
  inited = TRUE;

  iterator = CreateDeckLinkIteratorInstance ();
  if (iterator == NULL) {
    GST_ERROR ("no driver");
    return;
  }

  i = 0;
  ret = iterator->Next (&decklink);
  while (ret == S_OK) {
    devices[i].decklink = decklink;

    ret = decklink->QueryInterface (IID_IDeckLinkInput,
        (void **) &devices[i].input);
    if (ret != S_OK) {
      GST_WARNING ("selected device does not have input interface");
      return;
    }

    ret = decklink->QueryInterface (IID_IDeckLinkOutput,
        (void **) &devices[i].output);
    if (ret != S_OK) {
      GST_WARNING ("selected device does not have output interface");
      return;
    }

    ret = decklink->QueryInterface (IID_IDeckLinkConfiguration,
        (void **) &devices[i].config);
    if (ret != S_OK) {
      GST_WARNING ("selected device does not have config interface");
      return;
    }

    ret = iterator->Next (&decklink);
    i++;
  }

  n_devices = i;

  iterator->Release();
}
