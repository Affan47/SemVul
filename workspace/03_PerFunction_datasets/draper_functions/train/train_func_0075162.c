write_file(std::string& name, std::string& source)
{
	std::ofstream file(name.c_str());

	file << source;
	file.close();

	tmp_files.push_back(name);
}
