save2D_to_text_file(const string &file) const
{
	FILE	*f=os::fopen(file.c_str(),"wt");
	if (!f) return false;

	for (unsigned int i=0;i<x.size();i++)
		os::fprintf(f,"%f %f\n",x[i],y[i]);

	os::fclose(f);
	return true;
}
