operator>>(mrpt::utils::CStream &s,std::vector<std::string> &vec)	{
	uint32_t N;
	s>>N;
	vec.resize(N);
	for (size_t i=0;i<N;i++) s>>vec[i];
	return s;
}
