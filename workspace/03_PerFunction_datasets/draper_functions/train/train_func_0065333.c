flipBLKX(unsigned char* data, char out) {
  BLKXTable* blkx;
  uint32_t i;

  blkx = (BLKXTable*) data;

  FLIPENDIAN(blkx->fUDIFBlocksSignature);
  FLIPENDIAN(blkx->infoVersion);
  FLIPENDIAN(blkx->firstSectorNumber);
  FLIPENDIAN(blkx->sectorCount);

  FLIPENDIAN(blkx->dataStart);
  FLIPENDIAN(blkx->decompressBufferRequested);
  FLIPENDIAN(blkx->blocksDescriptor);

  FLIPENDIAN(blkx->reserved1);
  FLIPENDIAN(blkx->reserved2);
  FLIPENDIAN(blkx->reserved3);
  FLIPENDIAN(blkx->reserved4);
  FLIPENDIAN(blkx->reserved5);
  FLIPENDIAN(blkx->reserved6);

  flipUDIFChecksum(&(blkx->checksum), out);

  if(out) {
    for(i = 0; i < blkx->blocksRunCount; i++) {
      flipBLKXRun(&(blkx->runs[i]));
    }
    FLIPENDIAN(blkx->blocksRunCount);
  } else {
    FLIPENDIAN(blkx->blocksRunCount);
    for(i = 0; i < blkx->blocksRunCount; i++) {
      flipBLKXRun(&(blkx->runs[i]));
    }
  }


}
