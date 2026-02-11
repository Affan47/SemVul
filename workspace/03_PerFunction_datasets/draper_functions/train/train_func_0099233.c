clientdbCutoffDenied(struct in_addr addr)
{
    const char *key;
    int NR;
    int ND;
    double p;
    ClientInfo *c;
    if (!Config.onoff.client_db)
	return 0;
    key = xinet_ntoa(addr);
    c = (ClientInfo *) hash_lookup(client_table, key);
    if (c == NULL)
	return 0;


    if (squid_curtime - c->cutoff.time < CUTOFF_SECONDS)
	return 1;


    NR = c->Icp.n_requests - c->cutoff.n_req;
    if (NR < 150)
	NR = 150;
    ND = c->Icp.result_hist[LOG_UDP_DENIED] - c->cutoff.n_denied;
    p = 100.0 * ND / NR;
    if (p < 95.0)
	return 0;
    debug(1, 0) ("WARNING: Probable misconfigured neighbor at %s\n", key);
    debug(1, 0) ("WARNING: %d of the last %d ICP replies are DENIED\n", ND, NR);
    debug(1, 0) ("WARNING: No replies will be sent for the next %d seconds\n",
	CUTOFF_SECONDS);
    c->cutoff.time = squid_curtime;
    c->cutoff.n_req = c->Icp.n_requests;
    c->cutoff.n_denied = c->Icp.result_hist[LOG_UDP_DENIED];
    return 1;
}
