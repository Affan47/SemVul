load_trainset(std::string filename)
{


	std::string line;
	std::stringstream parse;
	int ssize = 100;

	char c[ssize];
	char delimiter = ',';


	std::vector<char> tmpcase;

	std::ifstream dataset_file(filename.c_str(), std::ios::in);

	if(!dataset_file)
	{
		std::cerr << "Cannot load training set file" << std::endl;
	}
	else
	{
		while( (getline(dataset_file, line))!= NULL )
		{
			parse << line;

			while( parse.getline(c,ssize,delimiter) )
				tmpcase.push_back(*c);

			parse.str("");
			parse.clear();

			training_set.push_back(tmpcase);
			tmpcase.clear();
		}
	}


	set_attributes();

}
