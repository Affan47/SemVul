startThread( ThreadContextRef aContextRef )
   {
      ThreadContextPtr  aContextPtr( NULLPTR );
      ThreadIdentifier  aThreadId( -1 );


      Guard    myGuard( theThreadManager.instance()->access() );

      try
      {


         aContextPtr =  aContextRef.createContext();

	 typedef int (* CloneFunctionType)(void *);
         aThreadId = ::clone
            (
	     CloneFunctionType(ThreadContext::cloneFrameFunction),

               aContextPtr->getStackTop(),
               aContextPtr->getShareMask(),
               aContextPtr
            );


         if( aThreadId.getScalar() == -1 )
         {
            aContextRef.setReturnCode( Thread::getKernelError() );
            aContextRef.setThreadState( THREAD_START_FAILED );
            aContextRef.destroyContext( aContextPtr );
         }
         else
         {
            theThreadMap[aThreadId] = aContextPtr;
            aContextPtr->setThreadState ( THREAD_RUNNING );
            theThreadCount++;
         }
      }


      catch( ExceptionRef aExcp )
      {
         aContextRef.setThreadState( THREAD_START_EXCEPTION );
         aContextRef.destroyContext(aContextPtr);
         throw;
      }
      catch( ... )
      {
         aContextRef.setThreadState( THREAD_START_EXCEPTION );
         aContextRef.destroyContext(aContextPtr);
         throw;
      }

      return aThreadId;
   }
