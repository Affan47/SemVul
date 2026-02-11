main(int argc, char **argv)
{
	try
	{
		printf(" ro-localization - Version 0.1 - Part of the MRPT\n");
		printf(" MRPT C++ Library: %s - Sources timestamp: %s\n", MRPT_getVersion().c_str(), MRPT_getCompilationDate().c_str());
		printf("-------------------------------------------------------------------\n");


		if (argc<2)
		{
			printf("Usage: %s <config.ini>\n\n",argv[0]);

			return -1;
		}

		iniFileName = argv[1];

		iniFile = new CConfigFile(iniFileName);

		TestParticlesLocalization();

		delete iniFile;

		return 0;
	}
	catch (exception &e)
	{
		cout << "Caught MRPT exception:\n" << e.what() << endl;

		return -1;
	}
	catch (...)
	{
		printf("Untyped exception!!");

		return -1;
	}
}
