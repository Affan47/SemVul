removeObserver(PlaylistObserver *observer)
{
    if(observer)
        observer->clearWatched();

    m_observers.removeAll(observer);
}
