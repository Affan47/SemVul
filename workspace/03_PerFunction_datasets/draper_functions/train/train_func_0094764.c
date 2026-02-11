rco_fread (rRCOFile_readhelper * rcoH, void *buf, uint32_t len)
{
  if (rcoH->tablesSize) {
    if (rcoH->memPos + len > rcoH->tablesSize)
      len = rcoH->tablesSize - rcoH->memPos;
    memcpy (buf, ((uint8_t *) rcoH->tables) + rcoH->memPos, len);

    rcoH->memPos += len;
    return len;
  } else {

    return fileread (rcoH->fp, buf, len);
  }
}
