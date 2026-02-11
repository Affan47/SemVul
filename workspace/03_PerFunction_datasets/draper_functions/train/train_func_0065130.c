main(int argc, char *argv[])
{
	CApp APP;

	if ( !APP.init(argc, argv) )
	{
		printf("init failed\n");
		return 1;
	}

	APP.run();
	APP.quit();

	return 0;
}
