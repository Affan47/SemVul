writeCascadeHeader(const string& weakLearnerName)
	{

		_shypFile << "<?xml version=\"1.0\"?>" << endl;
		_shypFile << "<cascade>" << endl;
		_shypFile << standardTag("algo", weakLearnerName, 1) << endl;

	}
