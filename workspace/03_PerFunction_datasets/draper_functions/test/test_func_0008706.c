camFPKdTreeFixDown(CamFPKdTreeBranch *pqueue, int k, int N)
{
    int j;
    CamFPKdTreeBranch tmp;
    while (2*k+1 < N) {
	j = 2*k+1;
	if (j < N-1 && pqueue[j].distance > pqueue[j+1].distance) j++;
	if (!(pqueue[k].distance > pqueue[j].distance)) break;
	EXCH(k, j);
	k = j;
    }
}
