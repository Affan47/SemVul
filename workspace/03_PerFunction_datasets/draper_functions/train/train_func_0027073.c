Init(char *StateFileName,CText *p)
{
   FILE *fp;
   int bSetDefaults = TRUE;


   FileName.print(".%s_dh.bin",StateFileName);

   if((fp = fopen(FileName.Buf,"r")) != NULL) {
      if(fread(Data,7,1,fp) != 1) {
         p->print("%s: error reading %s - %s\n",__FUNCTION__,FileName.Buf,
                  strerror(errno));
      }
      else {
         bSetDefaults = FALSE;
      }

      if(fread(&TxOffset,sizeof(TxOffset),1,fp) != 1) {
         p->print("%s: error reading %s - %s\n",__FUNCTION__,FileName.Buf,
                  strerror(errno));
      }
      fclose(fp);
   }

   if(bSetDefaults) {
      Data[0] = 0xff;
      Data[1] = 0xF0;
      Data[2] = 0xe0;
      Data[3] = 0;
      Data[4] = 0;
      Data[5] = 0;
      Data[6] = 0;
      TxOffset = 0;
   }
   memcpy(OrigData,Data,sizeof(OrigData));

   return 0;
}
