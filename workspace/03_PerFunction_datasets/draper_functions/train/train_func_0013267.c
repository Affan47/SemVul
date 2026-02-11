deleteLoaders()
{
	while (!_loaderList.isEmpty())
		delete _loaderList.takeFirst();
}
