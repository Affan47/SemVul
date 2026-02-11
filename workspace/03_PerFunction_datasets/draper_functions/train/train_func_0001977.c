MV_KillAllVoices
   (
   void
   )

   {
   VoiceNode * voice, * next;
   int        flags;

   if ( !MV_Installed )
      {
      MV_SetErrorCode( MV_NotInstalled );
      return( MV_Error );
      }

   flags = DisableInterrupts();


   for( voice = VoiceList.next; voice != &VoiceList; voice = next )
      {
      next = voice->next;
      if (voice->priority < MV_MUSIC_PRIORITY)
         {
         MV_Kill( voice->handle );
         }
      }

   RestoreInterrupts(flags);

   return( MV_Ok );
   }
