load( const string& fileName )
	{
		ifstream inFile;
		inFile.open(fileName.c_str());

		std::string line;
		int i=0;
		while(true) {
			i++;
			getline(inFile, line);
			if (inFile.eof()) break;
			if (!inFile) {
				std::cerr << "Error reading from " << fileName << std::endl;
				abort();
			}

			vector<string> token = tokenize(line.c_str());
			if (token.size() < 2) {
				cerr << "line " << i << " in " << fileName << " too short, skipping\n";
				continue;
			}

			int d = atoi( token[0].c_str() );
			double prob = log( atof( token[1].c_str() ) );
			dtable[ d ] = prob;
		}
	}
