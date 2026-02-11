OpenText(const std::string &File)
{
	int numLinks = 0;
	std::string line;
	std::ifstream infile;

	infile.open(File.c_str(), std::ifstream::in|std::ifstream::binary);
	if (!infile.is_open()) {
		return false;
	}

	while (getline(infile, line, (char)10 )) {
		int last = line.size()-1;
		if ((1 < last) && ((char)13  == line.at(last))) {
			line.erase(last);
		}
		if (AddLink(line)) {
			numLinks++;
		}
	}
	infile.close();

	if(numLinks == 0) {
		return false;
	}

	return true;
}
