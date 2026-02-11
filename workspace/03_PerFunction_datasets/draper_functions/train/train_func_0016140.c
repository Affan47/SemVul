WaitTillExit()
{


	try
	{
		if( FromSameThread() )
			throw "\n\tthis function can not be called from within the same thread!\n";


		if( !m_bRunning ) return;


#ifdef WINDOWS
		WaitForSingleObject(m_thread,INFINITE);
#else
		LPVOID lpv;

		pthread_join(m_thread,&lpv);
#endif
	}
	catch( char *psz )
	{
#ifdef WINDOWS
		MessageBoxA(NULL,&psz[2],"Fatal exception CThread::WaitTillExit",MB_ICONHAND);
		exit(-1);
#else
		cerr << "Fatal exception CThread::WaitTillExit: " << psz;
#endif

	}
}
