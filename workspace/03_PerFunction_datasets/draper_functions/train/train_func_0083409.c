AllocAudioBuf(int Bytes)
{
   NetAudio *pAudio;

   pAudio = (NetAudio *) malloc(sizeof(NetAudio) + Bytes);
   if(pAudio != NULL) {
      pAudio->Link = NULL;
      pAudio->Used = 0;
      pAudio->Flags = 0;
      pAudio->BufSN = AudioBufSn++;
   }
   return pAudio;
}
