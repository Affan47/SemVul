file_get_contents(const string filename)
{
	ifstream file_input(filename.c_str(),ios::binary);
    string line, file_contents = "";

    if(file_input.bad())
    {
		return "";
	}
	else
	{
	    while(file_input.good())
		{
			getline(file_input,line);
			file_contents += (line + "\n");
		}
	}
	file_input.close();

	return file_contents;
}
