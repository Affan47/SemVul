compute_most_recent_stats(vector<infinint> & data, vector<infinint> & ea,
					     vector<infinint> & total_data, vector<infinint> & total_ea) const
    {
	list<data_tree *>::const_iterator it = rejetons.begin();

	data_tree::compute_most_recent_stats(data, ea, total_data, total_ea);
	while(it != rejetons.end())
	{
	    (*it)->compute_most_recent_stats(data, ea, total_data, total_ea);
	    ++it;
	}
    }
