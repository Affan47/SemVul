hcompute(std::vector< std::vector<char> > ex)
{
	int pos_count = 0;
	int neg_count = 0;
	double p_pos = 0;
	double entropy = 0.;
	std::vector<char> tmp;


	for(std::vector< std::vector<char> >::iterator it = ex.begin(); it != ex.end(); ++it)
	{
		tmp = *it;
		if(tmp.at(0) == '1')
			pos_count++;
		else
			neg_count++;
	}
	tmp.clear();


	p_pos = (double)pos_count/(pos_count+neg_count);
	if(p_pos == 0 || p_pos == 1)
		entropy = 0;
	else
		entropy = -1*(p_pos*log2(p_pos)+(1-p_pos)*log2(1-p_pos));

	return entropy;
}
