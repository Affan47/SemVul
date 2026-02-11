findByNum(int x)
{
	int n = 0;
	VarList::Iterator it;
	for(it = begin(); it != end(); ++it) {
		if(n >= x)
			break;
		++n;
	}

	return it;
}
