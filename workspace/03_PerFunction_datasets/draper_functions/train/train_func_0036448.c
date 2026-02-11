~TransferHandler()
{
   if ( allowProduction != CGameOptions::Instance()->autoproduceammunition  ) {
      CGameOptions::Instance()->autoproduceammunition = allowProduction ;
      CGameOptions::Instance()->setChanged();
   }
}
