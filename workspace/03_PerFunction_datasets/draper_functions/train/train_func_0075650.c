LoadDataArray(const string &filename, std::vector<Data> &array)
{
	ifstream in(filename.c_str());
	return ReadDataArray(in, array);
}
