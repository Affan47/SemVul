extentKeyRead(off_t offset, io_func* io) {
  HFSPlusExtentKey* key;

  key = (HFSPlusExtentKey*) malloc(sizeof(HFSPlusExtentKey));

  if(!READ(io, offset, sizeof(HFSPlusExtentKey), key))
    return NULL;

  FLIPENDIAN(key->keyLength);
  FLIPENDIAN(key->forkType);
  FLIPENDIAN(key->fileID);
  FLIPENDIAN(key->startBlock);

  return (BTKey*)key;
}
