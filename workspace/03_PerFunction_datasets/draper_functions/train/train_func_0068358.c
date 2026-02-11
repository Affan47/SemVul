enableServerMode()
{
    SyncSourceAdmin::init(m_operations, this);
    SyncSourceBlob::init(m_operations, getCacheDir());
}
