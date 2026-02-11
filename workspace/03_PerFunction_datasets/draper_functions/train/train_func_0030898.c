thread_stop( struct thread_Settings* thread ) {

#ifdef HAVE_THREAD

    if ( ! thread_equalid( thread->mTID, thread_zeroid() ) ) {


        Condition_Lock( thread_sNum_cond );
        thread_sNum--;
        Condition_Signal( &thread_sNum_cond );
        Condition_Unlock( thread_sNum_cond );


        if ( thread_equalid( thread_getid(), thread->mTID ) ) {


            Settings_Destroy( thread );


#if   defined( HAVE_POSIX_THREAD )
            pthread_exit( NULL );
#else
            CloseHandle( thread->mHandle );
            ExitThread( 0 );
#endif
        } else {


#if   defined( HAVE_POSIX_THREAD )

#ifdef HAVE_PTHREAD_CANCEL
            pthread_cancel( thread->mTID );
#endif
#else


            TerminateThread( thread->mHandle, 0 );
#endif


            Settings_Destroy( thread );
        }
    }
#endif
}
