sSetDictionary (int i)
{
  setDictionary (langfnames[i]);
  setDictFromList (true);
  emit configChanged();
}
