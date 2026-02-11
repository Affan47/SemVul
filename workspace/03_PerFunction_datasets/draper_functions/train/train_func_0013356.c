PaUnixMutex_Unlock( PaUnixMutex* self )
{
    PaError result = paNoError;

    PA_ENSURE_SYSTEM( pthread_mutex_unlock( &self->mtx ), 0 );
#ifdef PTHREAD_CANCEL
	int oldState;
    PA_ENSURE_SYSTEM( pthread_setcancelstate( PTHREAD_CANCEL_ENABLE, &oldState ), 0 );
#endif

error:
    return result;
}
