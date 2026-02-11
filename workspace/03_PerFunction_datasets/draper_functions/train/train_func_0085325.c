pconnHistCount(int what, int i)
{
    if (i >= PCONN_HIST_SZ)
	i = PCONN_HIST_SZ - 1;

    if (what == 0)
	client_pconn_hist[i]++;
    else if (what == 1)
	server_pconn_hist[i]++;
    else
	assert(0);
}
