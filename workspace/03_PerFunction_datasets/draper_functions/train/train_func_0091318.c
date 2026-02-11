init(ht_coff_shared_data *Coff_shared, File *File)
{
	coff_shared = Coff_shared;
	file = File;

	validarea = new Area();
	validarea->init();

	Analyser::init();


	setLocationTreeOptimizeThreshold(100);
	setSymbolTreeOptimizeThreshold(100);
}
