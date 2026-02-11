extentDataRead(off_t offset, io_func* io) {
  HFSPlusExtentRecord* record;

  record = (HFSPlusExtentRecord*) malloc(sizeof(HFSPlusExtentRecord));

  if(!READ(io, offset, sizeof(HFSPlusExtentRecord), record))
    return NULL;

  flipExtentRecord(record);

  return (BTKey*)record;
}
