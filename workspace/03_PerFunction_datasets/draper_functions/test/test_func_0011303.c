readDriverDescriptorMap(AbstractFile* file, ResourceKey* resources) {
  BLKXTable* blkx;
  unsigned char* buffer;
  AbstractFile* bufferFile;
  DriverDescriptorRecord* record;
  int i;

  blkx = (BLKXTable*) (getDataByID(getResourceByKey(resources, "blkx"), -1)->data);

  buffer = (unsigned char*) malloc(512);
  bufferFile = createAbstractFileFromMemory((void**)&(buffer), 512);
  extractBLKX(file, bufferFile, blkx);
  bufferFile->close(bufferFile);

  record = (DriverDescriptorRecord*)buffer;
  flipDriverDescriptorRecord(record, FALSE);
  printf("sbSig:\t\t0x%x\n", record->sbSig);
  printf("sbBlkSize:\t0x%x\n", record->sbBlkSize);
  printf("sbBlkCount:\t0x%x\n", record->sbBlkCount);
  printf("sbDevType:\t0x%x\n", record->sbDevType);
  printf("sbDevId:\t0x%x\n", record->sbDevId);
  printf("sbData:\t\t0x%x\n", record->sbData);
  printf("sbDrvrCount:\t0x%x\n", record->sbDrvrCount);
  printf("ddBlock:\t0x%x\n", record->ddBlock);
  printf("ddSize:\t\t0x%x\n", record->ddSize);
  printf("ddType:\t\t0x%x\n", record->ddType);

  for(i = 0; i < (record->sbDrvrCount - 1); i++) {
    printf("\tddBlock:\t0x%x\n", record->ddPad[i].ddBlock);
    printf("\tddSize:\t\t0x%x\n", record->ddPad[i].ddSize);
    printf("\tddType:\t\t0x%x\n", record->ddPad[i].ddType);
  }

  free(buffer);
}
