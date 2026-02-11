main(int argc, char **argv)
{
	try
	{
		printf(" map-partition version 0.2 - Part of the MRPT\n");
		printf(" MRPT C++ Library: %s - Sources timestamp: %s\n", MRPT_getVersion().c_str(), MRPT_getCompilationDate().c_str());
		printf("-------------------------------------------------------------------\n");


		if (argc<2)
		{
			printf("Use: map-partition <file.simplemap> [nCut threshold 0-2]\n");
			mrpt::system::pause();
			return -1;
		}

		MAP_FILE = std::string( argv[1] );

		if (argc==3)
		{
			bool err = false;

			if (!sscanf(argv[2],"%f",&THRESHOLD_NCUT) )
				err = true;
			else
				if (THRESHOLD_NCUT<0 || THRESHOLD_NCUT>2)
					err = true;

			if (err)
			{
				printf("Use: map-partition <file.simplemap> [nCut threshold 0-2]\n");
				printf("\n\n Invalid nCut threshold: '%s'\n",argv[2]);
				mrpt::system::pause();
				return -1;
			}
		}


		Test();

		return 0;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl << "Program finished for an exception!!" << std::endl;
		mrpt::system::pause();
		return -1;
	}
	catch (...)
	{
		std::cerr << "Untyped exception!!" << std::endl;
		mrpt::system::pause();
		return -1;
	}
}
