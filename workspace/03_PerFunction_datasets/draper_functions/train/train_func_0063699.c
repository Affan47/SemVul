savemap( const ASCString& name, GameMap* gamemap )
{
#ifdef logging
   logtofile ( "loaders / tmaploaders::savemap / started " );
#endif

   tnfilestream filestream ( name, tnstream::writing );

   stream = &filestream;

   spfld = gamemap;


   {
      stream->writepchar ( getFullVersionString() );
      stream->writeWord ( fileterminator );
      stream->writeInt ( actmapversion  );

      writemap ( );
   }

   writefields ();
#ifdef WEATHERGENERATOR
   spfld->weatherSystem->write(filestream);
#endif
   stream->writeInt ( actmapversion );

   spfld = NULL;

   return 0;
}
