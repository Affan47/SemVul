isBoundaryConnector( const std::set< std::pair< int, int > > &links ) const
{
	int n = 0;

	for (int i = 0; i < sz - 1; i++)
		for (int j = i + 1; j < sz; j++)
		{
			int t1 = nodes[i]->tag, t2 = nodes[j]->tag;
			if ( nodes[i]->boundarynode && nodes[j]->boundarynode &&
			     links.find(std::make_pair(std::min(t1, t2), std::max(t1, t2))) != links.end() )
				n++;
		}

	return n > 1;
}
