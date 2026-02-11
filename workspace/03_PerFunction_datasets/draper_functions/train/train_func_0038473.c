SendToAll(int in_refnum, const void *in_data) {
    vector<int> clvec;
    int nsent = 0;

	if (netserver == NULL)
		return 0;

	kis_protocol_cache cache;

    netserver->FetchClientVector(&clvec);

    for (unsigned int x = 0; x < clvec.size(); x++) {
        if (SendToClient(clvec[x], in_refnum, in_data, &cache) > 0)
            nsent++;
    }

    return nsent;
}
