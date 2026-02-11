init(UResourceBundle *data, UErrorCode &status) {
  int32_t i = 0;
  fData->removeAll();
  UResourceBundle *t = NULL;
  for(i = 0; i < ures_getSize(data); i++) {
    t = ures_getByIndex(data, i, t, &status);
    fData->put(UnicodeString(ures_getKey(t), -1, US_INV), new ResourceBundle(t, status), status);
  }
  ures_close(t);
}
