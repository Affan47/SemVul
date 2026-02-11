eval (int x) const
{
	std::vector<int>::reverse_iterator it;
	int val;

	val = 0;
	for (it = rep->data.rbegin (); it != rep->data.rend (); ++it)
		val = val * x + *it;
	return val;
}
