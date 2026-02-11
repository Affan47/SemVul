SpawnThread( vtkThreadFunctionType f, void *userdata )
{
  int id;

#ifdef VTK_USE_WIN32_THREADS
  DWORD              threadId;
#endif

  for ( id = 0; id < VTK_MAX_THREADS; id++ )
    {
    if ( this->SpawnedThreadActiveFlagLock[id] == NULL )
      {
      this->SpawnedThreadActiveFlagLock[id] = vtkMutexLock::New();
      }
    this->SpawnedThreadActiveFlagLock[id]->Lock();
    if (this->SpawnedThreadActiveFlag[id] == 0)
      {

      this->SpawnedThreadActiveFlag[id] = 1;
      this->SpawnedThreadActiveFlagLock[id]->Unlock();
      break;
      }
    this->SpawnedThreadActiveFlagLock[id]->Unlock();
    }

  if ( id >= VTK_MAX_THREADS )
    {
    vtkErrorMacro( << "You have too many active threads!" );
    return -1;
    }

  this->SpawnedThreadInfoArray[id].UserData        = userdata;
  this->SpawnedThreadInfoArray[id].NumberOfThreads = 1;
  this->SpawnedThreadInfoArray[id].ActiveFlag =
    &this->SpawnedThreadActiveFlag[id];
  this->SpawnedThreadInfoArray[id].ActiveFlagLock =
    this->SpawnedThreadActiveFlagLock[id];


#ifdef VTK_USE_WIN32_THREADS


  this->SpawnedThreadProcessID[id] =
      CreateThread(NULL, 0, f,
             ((void *)(&this->SpawnedThreadInfoArray[id])), 0, &threadId);
  if (this->SpawnedThreadProcessID[id] == NULL)
    {
    vtkErrorMacro("Error in thread creation !!!");
    }
#endif

#ifdef VTK_USE_SPROC


  this->SpawnedThreadProcessID[id] =
    sproc( f, PR_SADDR, ( (void *)(&this->SpawnedThreadInfoArray[id]) ) );

#endif

#ifdef VTK_USE_PTHREADS


  pthread_attr_t attr;

#ifdef VTK_HP_PTHREADS
  pthread_attr_create( &attr );
#else
  pthread_attr_init(&attr);
#ifndef __CYGWIN__
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
#endif
#endif

#ifdef VTK_HP_PTHREADS
  pthread_create( &(this->SpawnedThreadProcessID[id]),
                  attr, f,
                  ( (void *)(&this->SpawnedThreadInfoArray[id]) ) );
#else
  pthread_create( &(this->SpawnedThreadProcessID[id]),
                  &attr,
                  reinterpret_cast<vtkExternCThreadFunctionType>(f),
                  ( (void *)(&this->SpawnedThreadInfoArray[id]) ) );
#endif

#endif

#ifndef VTK_USE_WIN32_THREADS
#ifndef VTK_USE_SPROC
#ifndef VTK_USE_PTHREADS


  vtkErrorMacro( << "Cannot spawn thread in a single threaded environment!" );
  this->SpawnedThreadActiveFlagLock[id]->Delete();
  id = -1;
#endif
#endif
#endif

  return id;
}
