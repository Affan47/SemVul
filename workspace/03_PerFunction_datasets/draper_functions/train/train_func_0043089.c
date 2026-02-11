t_timeout()
{
	SafeDeleteLock s(&d->sd);

	stop();
	resultsReady();
}
