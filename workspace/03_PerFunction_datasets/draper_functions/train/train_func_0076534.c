execute( void )
      throw( CommandFrameException )
   {
      GUARD;
      if( theWorkState == BUILDING )
      {
         theWorkState = EXECUTING;
         try
         {
            theWorkState = executeCommands();
         }
         catch( CommandFrameException aExcp )
         {
            theWorkState = NEVERCOMPLETED;
            throw ;
         }
         catch( ExceptionRef aExcp )
         {
            theWorkState = NEVERCOMPLETED;
            aExcp.addUnwindInfo( "CommandFrame::execute Exception handler" );
            throw ;
         }
         catch( ... )
         {
            theWorkState = NEVERCOMPLETED;
            throw CommandFrameException("Unhandled exception received",LOCATION);
         }
      }
      else
      {
         throw CommandFrameException( LOCATION );
      }

   }
