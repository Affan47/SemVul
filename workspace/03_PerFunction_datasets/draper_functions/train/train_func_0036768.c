clear()
{
    QMutexLocker locker( &dataMutex_ );

    maxLength_ = 0;
    matches_.clear();
}
