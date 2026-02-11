doRemove(char *name, time_t newts) {
	int i, remidx, remsize, r;
	FILE *f;
	if(loadBNL() != 0) return 1;
	for(i = 0; i < numcurbnlrecords; i++) {
		if(strcasecmp(cur_bnlrecords[i]->name, name) == 0) break;
	}
	if(i == numcurbnlrecords) {
		fprintf(stderr, "No such name in BNL.\n");
		return 1;
	}
	remidx = i;
	remsize = sizeof(struct bnl_record_hdr) + ntohl(cur_bnlrecords[remidx]->numsubnets) * sizeof(struct bnl_record_subnet);
	memmove(cur_bnlrecords[remidx], (char *)cur_bnlrecords[remidx] + remsize, cur_bnldata_len - ((char *)cur_bnlrecords[remidx] - cur_bnldata) - remsize);
	cur_bnldata_len -= remsize;
	cur_bnlhdr->timestamp = htonl(newts);
	r = sig_signandmakefile(cur_bnldata, cur_bnldata_len, cur_bnlsigdata, &cur_bnlsigdata_len);
	if(r != SIG_OK) {
		fprintf(stderr, "Error signing file\n");
		return 1;
	}
	f = fopen(bnl_filename, "w");
	if(!f) {
		fprintf(stderr, "Error opening file\n");
		return 1;
	}
	fwrite(cur_bnlsigdata, 1, cur_bnlsigdata_len, f);
	fclose(f);
	printf("Node %s removed.\n", name);
	return 0;
}
