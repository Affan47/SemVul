release( void )
      throw( SemaphoreException )
   {
      GUARD;
      SemaphoreOperationStatus   aStatus( SUCCESS );
      ThreadIdentifier           aTid( Thread::getThreadIdentifier() );
      GatewayClientIterator      aGItr( theClients.find(aTid) );

      if( aGItr != theClients.end() )
      {
         Count aC = (*aGItr).second;


         if( aC == 1 || Semaphore::isRecursionEnabled() == false )
         {
            if( ( aStatus = AbstractSemaphore::setUnlock( IPC_NOWAIT ) )
                == SUCCESS )
            {
               if( aTid == getOwnerId() )
               {
                  Semaphore::resetOwnerId();
               }
               else
               {
                  ;
               }

               if( aC == 1 )
               {
                  theClients.erase(aGItr);
               }
               else
               {
                  (*aGItr).second--;
               }
            }
            else
            {
               ;
            }
         }


         else
         {
            (*aGItr).second--;
         }
      }
      else
      {
         aStatus = UNAVAILABLE;
      }

      return aStatus;
   }
