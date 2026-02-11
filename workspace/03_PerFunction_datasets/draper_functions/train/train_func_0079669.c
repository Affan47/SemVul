FX_StopSound
   (
   int handle
   )

   {
   int status;

   status = MV_Kill( handle );
   if ( status != MV_Ok )
      {
      FX_SetErrorCode( FX_MultiVocError );
      return( FX_Warning );
      }

   return( FX_Ok );
   }
