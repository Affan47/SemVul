readData( vector<Example>& examples, NameMap& classMap,
								  vector<NameMap>& enumMaps, NameMap& attributeNameMap,
								  vector<RawData::eAttributeType>& attributeTypes )
	{

		ifstream inFile(_fileName.c_str());
		if ( !inFile.is_open() )
		{
			cerr << "\nERROR: Cannot open file <" << _fileName << ">!!" << endl;
			exit(1);
		}

		_dataRep = DR_SPARSE;
		_labelRep = LR_DENSE;

		if ( ! _headerFileName.empty() )
			readHeader( classMap, enumMaps, attributeNameMap, attributeTypes);
		else
			getHeaderInfoFromData(inFile, classMap, enumMaps, attributeNameMap, attributeTypes );
		readData(inFile, examples, classMap, enumMaps, attributeNameMap, attributeTypes);
	}
