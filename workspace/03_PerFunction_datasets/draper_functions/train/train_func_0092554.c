onSuccessPrivate( QByteArray data )
{
    qDebug() << objectName() << " request succeeded";


    if ( m_result == Request_Undefined )
    {
        m_data = data;
        m_result = Request_Success;


        success( data );
    }

    if ( !m_retry_timer.isActive() )
        emit result( this );

}
