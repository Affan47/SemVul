readHeader( NameMap& classMap,
									vector<NameMap>& enumMaps, NameMap& attributeNameMap,
									vector<RawData::eAttributeType>& attributeTypes )
	{
		cout << "Reading header file (" << _headerFileName << ")...";
		ifstream inHeaderFile(_headerFileName.c_str());
		if ( !inHeaderFile.is_open() )
		{
			cerr << "\nERROR: Cannot open file <" << _headerFileName << ">!!" << endl;
			exit(1);
		}

		string tmpLine;

		getline(inHeaderFile, tmpLine);
		istringstream ss;
		ss.imbue(_sparseLocale);
		ss.clear();
		ss.str(tmpLine);


		while (!ss.eof())
		{

			string tmpLab;
			ss >> tmpLab;

			if ( tmpLab.empty() ) continue;
			nor_utils::trim( tmpLab );
			if ( tmpLab.empty() ) continue;


			classMap.addName( tmpLab );
		}


		getline(inHeaderFile, tmpLine);
		ss.clear();
		ss.str(tmpLine);

		while (!ss.eof())
		{

			string tmpFeatName;
			ss >> tmpFeatName;

			if ( tmpFeatName.empty() ) continue;
			nor_utils::trim( tmpFeatName );
			if ( tmpFeatName.empty() ) continue;


			attributeNameMap.addName( tmpFeatName );
		}

		attributeTypes.resize( attributeNameMap.getNumNames() );
		fill( attributeTypes.begin(), attributeTypes.end(), RawData::ATTRIBUTE_NUMERIC );


		getline(inHeaderFile, tmpLine);
		if ( ! tmpLine.empty() )
		{
			cout << "Read weighting...";
			_weightOfClasses.clear();

			ss.clear();
			ss.str(tmpLine);
			for ( int i=0; i < classMap.getNumNames(); i++ )
			{

				AlphaReal tmpWeight;
				ss >> tmpWeight;

				_weightOfClasses.insert( make_pair<int, AlphaReal>( i, tmpWeight ) );
			}

		}

		inHeaderFile.close();

		cout << "Done." << endl;
	}
