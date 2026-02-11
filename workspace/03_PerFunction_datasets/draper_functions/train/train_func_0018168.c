longMessage( const QString &text, MessageType type )
{
    QMutexLocker locker( &m_lock );
    LongMessage msg;
    msg.first = text;
    msg.second = type;
    m_longMessageQueue.enqueue( msg );
    emit startTimer();
}
