KillDuplicates(const subset_type &dups)
{

	if( dups.size() == 0 )
		return;


	if( dups.size() == 1 ) {
		erase(dups[0]);
		return;
	}


	base_type copy;
	for( iterator i = begin(); i != end(); ++i ) {
		if( find(dups.begin(), dups.end(), i) == dups.end() ) {

			copy.push_back(*i);
		}
	}


	clear();
	base_type::operator=(copy);
}
