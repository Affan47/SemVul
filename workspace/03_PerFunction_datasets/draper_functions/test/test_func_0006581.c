Randomize(void) {
   int i, uuidGenerated = 0;

#ifdef _UUID_UUID_H
   uuid_generate(uuidData);
   ReverseBytes(&uuidData[0], 4);
   ReverseBytes(&uuidData[4], 2);
   ReverseBytes(&uuidData[6], 2);
   uuidGenerated = 1;
#endif
#if defined (_RPC_H) || defined (__RPC_H__)
   UUID MsUuid;
   if (UuidCreate(&MsUuid) == RPC_S_OK) {
      memcpy(uuidData, &MsUuid, 16);
      uuidGenerated = 1;
   }
#endif

   if (!uuidGenerated) {
      cerr << "Warning! Unable to generate a proper UUID! Creating an improper one as a last\n"
           << "resort! Windows 7 may crash if you save this partition table!\a\n";
      for (i = 0; i < 16; i++)
         uuidData[i] = (unsigned char) (256.0 * (rand() / (RAND_MAX + 1.0)));
   }
}
