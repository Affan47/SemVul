auxiliary_thread_launcher_LIN( void *param )
		{
			try
			{
			TAuxThreadLaucher   *d = reinterpret_cast<TAuxThreadLaucher*>(param);

			TAuxThreadLaucher	localCopy = *d;

	#ifdef MRPT_OS_WINDOWS

			d->myWindowsId = (unsigned long)GetCurrentThreadId();
			d->win_sem.release();

	#else

			delete d;
			d = NULL;
	#endif


			localCopy.ptrFunc( localCopy.param );
			}
			catch(std::exception &e)
			{
				std::cout << "Exception in [auxiliary_thread_launcher_LIN/WIN]!!!:\n" << e.what();
			}
			catch(...)
			{
				std::cout << "Untyped exception in [auxiliary_thread_launcher_LIN/WIN]!!!\n";
			}
			return NULL;
		}
