open_source(const std::string &filename)
{
	if (datafile_handle == -1)
		open();

	return new CL_InputSource_Datafile(filename, this);
}
