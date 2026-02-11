writeATAPI(int pNum, AbstractFile* file, unsigned int BlockSize, ChecksumFunc dataForkChecksum, void* dataForkToken, ResourceKey **resources, NSizResource** nsizIn) {
  AbstractFile* bufferFile;
  BLKXTable* blkx;
  ChecksumToken uncompressedToken;
  NSizResource* nsiz;
  CSumResource csum;
  char* atapi;

  memset(&uncompressedToken, 0, sizeof(uncompressedToken));

  atapi = (char*) malloc(ATAPI_SIZE * SECTOR_SIZE);
  printf("malloc: %p %d\n", atapi, ATAPI_SIZE * SECTOR_SIZE); fflush(stdout);
  memcpy(atapi, atapi_data, ATAPI_SIZE * SECTOR_SIZE);
  bufferFile = createAbstractFileFromMemory((void**)&atapi, ATAPI_SIZE * SECTOR_SIZE);

  if(BlockSize != SECTOR_SIZE)
  {
    blkx = insertBLKX(file, bufferFile, ATAPI_OFFSET, BlockSize / SECTOR_SIZE, pNum, CHECKSUM_CRC32,
                &BlockCRC, &uncompressedToken, dataForkChecksum, dataForkToken, NULL, 0);
  }
  else
  {
    blkx = insertBLKX(file, bufferFile, ATAPI_OFFSET, ATAPI_SIZE, pNum, CHECKSUM_CRC32,
                &BlockCRC, &uncompressedToken, dataForkChecksum, dataForkToken, NULL, 0);
  }

  bufferFile->close(bufferFile);
  free(atapi);

  blkx->checksum.data[0] = uncompressedToken.crc;

  csum.version = 1;
  csum.type = CHECKSUM_MKBLOCK;
  csum.checksum = uncompressedToken.block;

  char pName[100];
  sprintf(pName, "Macintosh (Apple_Driver_ATAPI : %d)", pNum + 1);
  *resources = insertData(*resources, "blkx", pNum, pName, (const char*) blkx, sizeof(BLKXTable) + (blkx->blocksRunCount * sizeof(BLKXRun)), ATTRIBUTE_HDIUTIL);
  *resources = insertData(*resources, "cSum", 1, "", (const char*) (&csum), sizeof(csum), 0);

  nsiz = (NSizResource*) malloc(sizeof(NSizResource));
  memset(nsiz, 0, sizeof(NSizResource));
  nsiz->isVolume = FALSE;
  nsiz->blockChecksum2 = uncompressedToken.block;
  nsiz->partitionNumber = 1;
  nsiz->version = 6;
  nsiz->next = NULL;

  if((*nsizIn) == NULL) {
    *nsizIn = nsiz;
  } else {
    nsiz->next = (*nsizIn)->next;
    (*nsizIn)->next = nsiz;
  }

  free(blkx);

  pNum++;

  if(BlockSize != SECTOR_SIZE && (USER_OFFSET -  (ATAPI_OFFSET + (BlockSize / SECTOR_SIZE))) > 0)
    pNum = writeFreePartition(pNum, file, ATAPI_OFFSET + (BlockSize / SECTOR_SIZE), USER_OFFSET - (ATAPI_OFFSET + (BlockSize / SECTOR_SIZE)), resources);

  return pNum;
}
