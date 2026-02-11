registerFactory()
{
	URIStreamOpener::defaultOpener().registerStreamFactory("http", new HTTPStreamFactory);
}
