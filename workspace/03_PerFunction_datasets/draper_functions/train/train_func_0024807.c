writeApplePartitionMap(AbstractFile* file, Partition* partitions, ChecksumFunc dataForkChecksum, void* dataForkToken, ResourceKey **resources, NSizResource** nsizIn) {
  AbstractFile* bufferFile;
  BLKXTable* blkx;
  ChecksumToken uncompressedToken;
  Partition* buffer;
  NSizResource* nsiz;
  CSumResource csum;

  buffer = (Partition*) malloc(PARTITION_SIZE * SECTOR_SIZE);
  memcpy(buffer, partitions, PARTITION_SIZE  * SECTOR_SIZE);
  memset(&uncompressedToken, 0, sizeof(uncompressedToken));

  flipPartition(buffer, TRUE, SECTOR_SIZE);

  bufferFile = createAbstractFileFromMemory((void**)&buffer, PARTITION_SIZE * SECTOR_SIZE);

  blkx = insertBLKX(file, bufferFile, PARTITION_OFFSET, PARTITION_SIZE, 0, CHECKSUM_CRC32,
              &BlockCRC, &uncompressedToken, dataForkChecksum, dataForkToken, NULL);

  bufferFile->close(bufferFile);

  *((uint32_t*)blkx->checksum.data) = uncompressedToken.crc;

  csum.version = 1;
  csum.type = CHECKSUM_MKBLOCK;
  csum.checksum = uncompressedToken.block;

  *resources = insertData(*resources, "blkx", 0, "Apple (Apple_partition_map : 1)", (const char*) blkx, sizeof(BLKXTable) + (blkx->blocksRunCount * sizeof(BLKXRun)), ATTRIBUTE_HDIUTIL);
  *resources = insertData(*resources, "cSum", 0, "", (const char*) (&csum), sizeof(csum), 0);

  nsiz = (NSizResource*) malloc(sizeof(NSizResource));
  memset(nsiz, 0, sizeof(NSizResource));
  nsiz->isVolume = FALSE;
  nsiz->blockChecksum2 = uncompressedToken.block;
  nsiz->partitionNumber = 0;
  nsiz->version = 6;
  nsiz->next = NULL;

  if((*nsizIn) == NULL) {
    *nsizIn = nsiz;
  } else {
    nsiz->next = (*nsizIn)->next;
    (*nsizIn)->next = nsiz;
  }

  free(buffer);
  free(blkx);
}
