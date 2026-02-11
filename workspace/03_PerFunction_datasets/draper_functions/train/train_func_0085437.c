saveToTextFile(const std::string &file) const
{
	MRPT_START

	FILE	*f=os::fopen(file.c_str(),"wt");
	if (!f) return;

	os::fprintf(f,"%f %f\n", mean.x(), mean.y() );

	os::fprintf(f,"%f %f\n", cov(0,0),cov(0,1) );
	os::fprintf(f,"%f %f\n", cov(1,0),cov(1,1) );

	os::fclose(f);

	MRPT_END
}
