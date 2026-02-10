savenwgame( tnstream* strm, const GameMap* gamemap )
{

   PackageManager::storeData( gamemap );

   spfld = const_cast<GameMap*>(gamemap);

   stream = strm;

   stream->writepchar ( getFullVersionString() );
   stream->writeWord ( fileterminator );

   stream->writeInt ( actnetworkversion );

   writemap ();

   writemessages();

   stream->writeInt ( actnetworkversion );

   writefields ( );

   writedissections();

   if ( spfld->replayinfo )
      spfld->replayinfo->write ( *stream );


   writeAI();

   stream->writeInt ( actnetworkversion );

   spfld = NULL;

   return 0;
}
