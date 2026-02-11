thread_attribute_init( pthread_attr_t *attr,
			int joinable, size_t stacksz )
{
	int j = ( joinable ? PTHREAD_CREATE_JOINABLE
				: PTHREAD_CREATE_DETACHED );

	if( ( errno = pthread_attr_init( attr ) ) )
		msglog( MSG_FATAL|LOG_ERRNO, "thread_attribute_init: " \
			"pthread_attr_init" );

	if( ( errno = pthread_attr_setdetachstate( attr, j ) ) )
		msglog( MSG_FATAL|LOG_ERRNO, "thread_attribute_init: " \
			"pthread_attr_setdetachstate" );

	if( stacksz && ( errno = pthread_attr_setstacksize( attr, stacksz ) ) )
		msglog( MSG_FATAL|LOG_ERRNO, "thread_attribute_init: " \
			"pthread_attr_setstacksize %d", stacksz );

        if( ( errno = pthread_attr_setscope( attr, PTHREAD_SCOPE_SYSTEM ) ) )
                msglog( MSG_FATAL|LOG_ERRNO, "thread_attribute_init: " \
                       "pthread_attr_setscope PTHREAD_SCOPE_SYSTEM" );
}
