test_cases(std::string filename)
{


	std::string line;
	std::stringstream parse;
	int ssize = 100;
	char c[ssize];
	char delimiter = ',';


	std::vector<char> tmpcase;


	dectree_node* tmp_node;
	std::vector<bool> results;
	int good_classif = 0;
	int bad_classif = 0;

	std::ifstream dataset_file(filename.c_str(), std::ios::in);

	if(!dataset_file)
	{
		std::cerr << "Cannot load test file" << std::endl;
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


			tmp_node = dbst;


			while(tmp_node != NULL && !(tmpcase.empty()))
			{

				if(!(tmp_node->type.compare("terminal")))
				{
					parse << tmp_node->output_id;


					if(*(parse.str().c_str())==tmpcase.at(0))
					{
						results.push_back(true);
						good_classif++;
					}
					else
					{
						results.push_back(false);
						bad_classif++;
					}

					parse.str("");
					parse.clear();
					tmp_node = NULL;
				}
				else
				{
					if(tmpcase.at(tmp_node->attribute_id)=='0')
					{

						tmp_node = tmp_node->f;
					}
					else
					{

						tmp_node = tmp_node->t;
					}
				}
			}

			tmpcase.clear();
		}
	}

	per_error = (double)bad_classif / (good_classif+bad_classif);
	return results;
}
