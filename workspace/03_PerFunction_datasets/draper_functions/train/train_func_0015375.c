checkInput(const string& line, int numColumns) const
	{
		istringstream ss(line);
		ss.imbue( locale(locale(), new nor_utils::white_spaces(_sepChars) ) );

		string tmp;
		bool inputValid = true;

		if (_hasExampleName)
			ss >> tmp;

		if (!_hasClassEnd)
			ss >> tmp;

		for (int j = 0; j < numColumns; ++j)
		{
			if ( ss.eof() )
			{
				inputValid = false;
				break;
			}

			ss >> tmp;

			if ( !nor_utils::is_number(tmp) )
			{
				inputValid = false;
				break;
			}
		}

		if (_hasClassEnd)
			ss >> tmp;
		if ( tmp.empty() )
			inputValid = false;

		return inputValid;
	}
