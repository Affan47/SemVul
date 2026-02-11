getMainXRefEntriesOffset()
{
  Guint mainXRefEntriesOffset = 0;

  if (isLinearized()) {
    mainXRefEntriesOffset = getLinearization()->getMainXRefEntriesOffset();
  }

  return mainXRefEntriesOffset;
}
