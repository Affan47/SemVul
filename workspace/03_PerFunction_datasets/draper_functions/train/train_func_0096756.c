log(const char *prefix) const
{
  time_t idTime = getTimestamp();

  char timeBuf[500];

  struct tm *idTm = NULL;

  if (idTime != -1) {
    idTm = localtime(&idTime);
  }
  if (idTm != NULL) {
    strftime(timeBuf, sizeof(timeBuf), "%c", idTm);
  }
  else {
    snprintf(timeBuf, sizeof(timeBuf), "NULL");
  }

  ArLog::log(ArLog::Normal,
             "%s%smap %s %s%s checksum = \"%s\" size = %i  time = %s (%i)",
             ((prefix != NULL) ? prefix : ""),
             ((prefix != NULL) ? " " : ""),
             getFileName(),
             (!ArUtil::isStrEmpty(getSourceName()) ? "source " : ""),
             (!ArUtil::isStrEmpty(getSourceName()) ? getSourceName() : ""),
             getDisplayChecksum(),
             getSize(),
             timeBuf,
             idTime);

}
