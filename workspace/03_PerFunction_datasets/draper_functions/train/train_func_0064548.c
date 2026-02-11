setAutoDelete( bool autoDelete )
{
    if( autoDelete )
    {
        if( isFinished() )
            deleteLater();
        connect( this, SIGNAL(done(ThreadWeaver::Job*)), this, SLOT(deleteLater()) );
    }
    else
    {
        disconnect( this, SIGNAL(done(ThreadWeaver::Job*)), this, SLOT(deleteLater()) );
    }
}
