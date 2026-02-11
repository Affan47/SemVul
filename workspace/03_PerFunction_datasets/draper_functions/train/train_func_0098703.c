release( void )
      throw( SemaphoreException )
   {
      GUARD;
      SemaphoreOperationStatus   aStatus( SUCCESS );


      aStatus = setLock( IPC_NOWAIT );

      return aStatus;
   }
