goToFirstFile()
{
  zipError=UNZ_OK;
  if(mode!=mdUnzip) {
    qWarning("QuaZip::goToFirstFile(): ZIP is not open in mdUnzip mode");
    return false;
  }
  zipError=unzGoToFirstFile(unzFile_f);
  hasCurrentFile_f=zipError==UNZ_OK;
  return hasCurrentFile_f;
}
