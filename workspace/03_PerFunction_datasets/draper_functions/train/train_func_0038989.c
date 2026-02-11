main(int argc, char **argv)
{
	try
	{
		if (argc!=1 && argc!=3)
		{
			cerr << "Usage: " << endl;
			cerr << argv[0] << endl;
			cerr << argv[0] << " <image1> <image2>" << endl;
			return 1;
		}

		if (argc==3)
		{
			file1 = string(argv[1]);
			file2 = string(argv[2]);
		}

		DemoFeatures();
		return 0;
	}
	catch(exception &e)
	{
		cerr << e.what();
		return 1;
	}
}
