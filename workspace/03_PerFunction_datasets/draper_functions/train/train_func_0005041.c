get_marked_strings(const list<string>& lks, const list<string>& lcs)
{
    list< string > lms;

    c_lststr lks_it = lks.begin();
    c_lststr lcs_it = lcs.begin();

    while(lks_it != lks.end())
	if(lcs_it != lcs.end())
	{
	    lms.push_back(mark_mistakes(*lks_it, *lcs_it));
	    ++lks_it;
	    ++lcs_it;
	}
	else
	{
	    lms.push_back( string((*lks_it).size(), INCORRECT_MARKER) );
	    ++lks_it;
	}

    return lms;
}
