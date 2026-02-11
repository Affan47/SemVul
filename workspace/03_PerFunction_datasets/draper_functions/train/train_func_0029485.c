ConvertProtocol(
   ProtoData *pProtoDat,
   Protocol InputProto,
   Protocol OutputProto,
   int bNewStream)
{
   char *Buf;
   int Len;
   int i;

   if(ProtoConvert[InputProto][OutputProto] != NULL) {
      for(i = 0; i < MAX_CONV_PACKETS; i++) {
         if((Len = pProtoDat[InputProto].DataLen[i]) > 0) {
            Buf = pProtoDat[InputProto].Data[i];
            if(i == 0 && bNewStream) {
               ProtoConvert[InputProto][OutputProto](pProtoDat,Buf,Len,TRUE);
            }
            else {
               ProtoConvert[InputProto][OutputProto](pProtoDat,Buf,Len,FALSE);
            }
         }
      }
   }
   pProtoDat[OutputProto].bDataValid = TRUE;
}
