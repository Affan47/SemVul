getOwnerRecursionQueueLength( void )
   {
      Counter  aCount(-1);

      if( this->isAnOwner() == true )
      {
         GUARD;
         aCount = (*(theClients.find(Thread::getThreadIdentifier()))).second;
      }
      else
      {
         ;
      }

      return aCount;
   }
