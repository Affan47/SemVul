createSemaphore
      (
         SemaphoreIdentifierRef  aIdentifier,
         CreateDisposition       disp,
         bool                    Recursive,
         bool                    Balking
      ) throw( SemaphoreException )
   {
      Short   aSid( aIdentifier.getScalar() );

      if( aSid < 0 || aSid > getSemaphoreCount() )
      {
         throw SemaphoreException
            (
               "Invalid Semaphore identifier",
               LOCATION,
               Exception::CONTINUABLE
            );
      }
      else
      {
         ;
      }

      return this->resolveSemaphore ( aIdentifier, aSid, disp,
            Recursive, Balking, DEFAULT_COUNT);
   }
