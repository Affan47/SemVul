KfwumUploadFirmware(struct ipmi_intf * intf,
                               unsigned char * pBuffer, unsigned long totalSize)
{
   tKFWUM_Status status = KFWUM_STATUS_ERROR;
   unsigned long address    = 0x0;
   unsigned char writeSize;
   unsigned char oldWriteSize;
   unsigned long lastAddress = 0;
   unsigned char sequenceNumber = 0;
   unsigned char retry = FWUM_MAX_UPLOAD_RETRY;
   unsigned char isLengthValid = 1;

   do
   {
      writeSize = saveFirmwareInfo.bufferSize - saveFirmwareInfo.overheadSize;


      if( address + writeSize > totalSize )
      {
         writeSize = (totalSize - address);
      }

      else if(((address % KFWUM_PAGE_SIZE) + writeSize) > KFWUM_PAGE_SIZE)
      {
         writeSize = (KFWUM_PAGE_SIZE - (address % KFWUM_PAGE_SIZE));
      }

      oldWriteSize = writeSize;
      status = KfwumSaveFirmwareImage(intf, sequenceNumber, address,
                                                &pBuffer[address], &writeSize);

      if((status != KFWUM_STATUS_OK) && (retry-- != 0))
      {
         address = lastAddress;
         status = KFWUM_STATUS_OK;
      }
      else if( writeSize == 0 )
      {
         status = KFWUM_STATUS_ERROR;
      }
      else
      {
         if(writeSize != oldWriteSize)
         {
            printf("Adjusting length to %d bytes \n", writeSize);
            saveFirmwareInfo.bufferSize -= (oldWriteSize - writeSize);
         }

         retry = FWUM_MAX_UPLOAD_RETRY;
         lastAddress = address;
         address+= writeSize;
      }

      if(status == KFWUM_STATUS_OK)
      {
         if((address % 1024) == 0)
         {
            KfwumShowProgress((const unsigned char *)\
                                 "Writting Firmware in Flash",address,totalSize);
         }
         sequenceNumber++;
      }

   }while((status == KFWUM_STATUS_OK) && (address < totalSize  ));

   if(status == KFWUM_STATUS_OK)
   {
      KfwumShowProgress((const unsigned char *)\
                                       "Writting Firmware in Flash", 100 , 100 );
   }

   return(status);
}
