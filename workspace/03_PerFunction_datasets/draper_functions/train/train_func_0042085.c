UnLock()
{
if ( m_lockcount > 0 )
    {
    --m_lockcount;
    }
pthread_mutex_unlock( (pthread_mutex_t*)&m_mutex );
}
