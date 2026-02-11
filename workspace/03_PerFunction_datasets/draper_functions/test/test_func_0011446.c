rankGroup(int groupType) const
{
	static int rankgroups[5] = {
		gGeneral,
		gUser,
		gPrivate,
		gAgents,
		gNotInList,
	};

	int n;
	for(n = 0; n < (int)sizeof(rankgroups); ++n) {
		if(rankgroups[n] == groupType)
			break;
	}
	if(n == sizeof(rankgroups))
		return sizeof(rankgroups)-1;

	return n;
}
