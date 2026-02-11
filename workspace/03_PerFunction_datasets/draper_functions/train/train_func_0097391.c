operator<<(mrpt::utils::CStream &s,const std::vector<std::string> &vec)	{
	uint32_t N=static_cast<uint32_t>(vec.size());
	s<<N;
	for (size_t i=0;i<N;i++) s<<vec[i];
	return s;
}
