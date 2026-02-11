ConsumeAudio(NetAudio *pAudio)
{
   if(pAudio->Users > 0) {
      pAudio->Users--;
   }
   else {
      CORE_DUMP();
   }
}
