getEntriesCount()const
{
  QuaZip *fakeThis=(QuaZip*)this;
  fakeThis->zipError=UNZ_OK;
  if(mode!=mdUnzip) {
    qWarning("QuaZip::getEntriesCount(): ZIP is not open in mdUnzip mode");
    return -1;
  }
  unz_global_info globalInfo;
  if((fakeThis->zipError=unzGetGlobalInfo(unzFile_f, &globalInfo))!=UNZ_OK)
    return zipError;
  return (int)globalInfo.number_entry;
}
