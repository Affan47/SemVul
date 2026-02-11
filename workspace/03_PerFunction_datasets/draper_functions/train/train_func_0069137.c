Start()
{
	try
	{
		if( FromSameThread() )
		{
			throw "\n\tit is illegal for a thread to attempt to start itself!\n";
		}


		m_mutex.Lock();
		if( m_bRunning )
		{
			m_mutex.Unlock();
			return TRUE;
		}

		m_mutex.Unlock();


		if( m_dwObjectCondition & THREAD_CREATION )
			m_dwObjectCondition = m_dwObjectCondition ^ THREAD_CREATION;

#ifdef WINDOWS
		if( m_thread ) CloseHandle(m_thread);
#ifdef USE_BEGIN_THREAD
		m_thread = (HANDLE )_beginthreadex(NULL,(unsigned int)m_stackSize,_THKERNEL,(LPVOID)this,0,&m_dwId);
#else
		m_thread = CreateThread(NULL,m_stackSize ,_THKERNEL,(LPVOID)this,0,&m_dwId);
#endif
		if( !m_thread )
		{
			perror("thread creation failed");
			m_dwObjectCondition |= THREAD_CREATION;
			m_state = ThreadStateFault;
			return FALSE;
		}
#else
		pthread_attr_t attr;

		pthread_attr_init(&attr);

#ifdef VMS
		if( m_stackSize == 0 )
			pthread_attr_setstacksize(&attr,PTHREAD_STACK_MIN*10);
#endif
		if( m_stackSize != 0 )
			pthread_attr_setstacksize(&attr,m_stackSize);

		int error = pthread_create(&m_thread,&attr,_THKERNEL,(LPVOID)this);

		if( error != 0 )
		{
			m_dwObjectCondition |= THREAD_CREATION;
			m_state = ThreadStateFault;

#if defined(HPUX) || defined(SUNOS) || defined(LINUX)
			switch(error)
			{

			case EINVAL:
				cerr << "error: attr in an invalid thread attributes object\n";
				break;
			case EAGAIN:
				cerr << "error: the necessary resources to create a thread are not\n";
				cerr << "available.\n";
				break;
			case EPERM:
				cerr << "error: the caller does not have the privileges to create\n";
				cerr << "the thread with the specified attr object.\n";
				break;
#if defined(HPUX)
			case ENOSYS:

				cerr << "error: pthread_create not implemented!\n";
				if( __is_threadlib_linked()==0 )
				{
					cerr << "error: threaded library not being used, improper linkage \"-lpthread -lc\"!\n";
				}
				break;
#endif
			default:
				cerr << "error: an unknown error was encountered attempting to create\n";
				cerr << "the requested thread.\n";
				break;
			}
#else
			cerr << "error: could not create thread, pthread_create failed (" << error << ")!\n";
#endif
			return FALSE;
		}
#endif
	}
	catch (char *psz)
	{
#ifdef WINDOWS
		MessageBoxA(NULL,&psz[2],"Fatal exception CThread::Start",MB_ICONHAND);
#else
		cerr << "Fatal exception CThread::Start():" << psz;
#endif
		exit(-1);
	}
	return TRUE;
}
