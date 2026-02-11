getRefData(int gid, GList<GSeqData>& ref_data) {
	int ri=-1;
	GSeqData f(gid);
	GSeqData* r=NULL;
	if (ref_data.Found(&f,ri))
		r=ref_data[ri];
	return r;
}
