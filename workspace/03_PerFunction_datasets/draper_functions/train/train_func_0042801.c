MV_VoicePlaying
   (
   int handle
   )

   {
   VoiceNode *voice;

   if ( !MV_Installed )
      {
      MV_SetErrorCode( MV_NotInstalled );
      return( FALSE );
      }

   voice = MV_GetVoice( handle );

   if ( voice == NULL )
      {
      return( FALSE );
      }

   return( TRUE );
   }
