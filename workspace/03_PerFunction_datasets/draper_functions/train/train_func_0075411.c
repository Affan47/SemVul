vectorToTextFile( const vector<double> &vec, const string &fileName, bool append, bool byRows  )
{
	FILE	*f=os::fopen(fileName.c_str(),append ? "at" : "wt");
	if (!f) return false;

	for (vector<double>::const_iterator	it=vec.begin();it!=vec.end();++it)
		os::fprintf(f,byRows ? "%e ":"%e\n",*it);

	if (byRows) os::fprintf(f,"\n");

	os::fclose(f);
	return true;
}
