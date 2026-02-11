indegree () const
{
	e_const_iterator eit;
	int cnt = 0;

	for (eit = e_begin (); eit != e_end (); ++eit)
		if ((*eit)->directed && ((*eit)->w == this))
			++cnt;
	return cnt;
}
