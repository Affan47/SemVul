CheckNewConnection( void ) const
{
    tASSERT( IsOpen() );

    int	available=-1;


    if ( tRecorder::IsRunning() )
        return this;


#ifdef DEBUG
    if ( sn_ResetSocket )
    {
        sn_ResetSocket = false;
        Reset();
    }
#endif


    int ret = ioctl (socket_, FIONREAD, &available);
    if ( ret == -1)
    {
        switch ( ANET_Error() )
        {
        case nSocketError_Reset:
            Reset();
            break;
        case nSocketError_Ignore:
            break;
        default:
            Sys_Error ("UDP: ioctlsocket (FIONREAD) failed\n");
            break;
        }
    }

    if ( ret >= 0 )
    {


        return this;
    }

    return NULL;
}
