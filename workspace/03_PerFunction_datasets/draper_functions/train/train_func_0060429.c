setLimit( Counter aLimit )
      throw( SemaphoreException )
   {
      if ( Thread::getThreadIdentifier() == getOwnerId() )
      {
         theMaxListeners = aLimit;
      }
      else
      {
         throw SemaphoreException
            (
               "Not authorized to set limit",
               LOCATION,
               Exception::CONTINUABLE
            );
      }
   }
