CreateListenCallback()
{
	return new CCallback1<CListenManager, int>( this, &CListenManager::ListenCallback );
}
