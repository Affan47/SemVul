scanRight(unsigned v, int idx)
{
	checkVersionAndIdx(v, idx);
	while (idx < versions[v].size() - 1) {
		if (versions[v][++idx] != 0) return idx;
	}
	return -1;
}
