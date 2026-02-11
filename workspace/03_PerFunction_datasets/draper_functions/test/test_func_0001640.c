list_all(int argc, char* argv[])
{
	for(int i=0;i<argc;++i) {
		if (argc > 1 && !opt_crc)
			cout << "File: " << argv[i] << endl;
		png_print(argv[i]);
	}
}
