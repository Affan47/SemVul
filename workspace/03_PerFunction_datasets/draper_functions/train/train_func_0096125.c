RecomputeCRCs(void) {
   uint32_t crc, hSize;
   int littleEndian = 1;


   if (mainHeader.headerSize > sizeof(GPTHeader))
      hSize = secondHeader.headerSize = mainHeader.headerSize = HEADER_SIZE;
   else
      hSize = secondHeader.headerSize = mainHeader.headerSize;

   if ((littleEndian = IsLittleEndian()) == 0) {
      ReversePartitionBytes();
      ReverseHeaderBytes(&mainHeader);
      ReverseHeaderBytes(&secondHeader);
   }


   crc = chksum_crc32((unsigned char*) partitions, numParts * GPT_SIZE);
   mainHeader.partitionEntriesCRC = crc;
   secondHeader.partitionEntriesCRC = crc;
   if (littleEndian == 0) {
      ReverseBytes(&mainHeader.partitionEntriesCRC, 4);
      ReverseBytes(&secondHeader.partitionEntriesCRC, 4);
   }


   mainHeader.headerCRC = 0;
   secondHeader.headerCRC = 0;

   crc = chksum_crc32((unsigned char*) &mainHeader, hSize);
   if (littleEndian == 0)
      ReverseBytes(&crc, 4);
   mainHeader.headerCRC = crc;
   crc = chksum_crc32((unsigned char*) &secondHeader, hSize);
   if (littleEndian == 0)
      ReverseBytes(&crc, 4);
   secondHeader.headerCRC = crc;

   if (littleEndian == 0) {
      ReverseHeaderBytes(&mainHeader);
      ReverseHeaderBytes(&secondHeader);
      ReversePartitionBytes();
   }
}
