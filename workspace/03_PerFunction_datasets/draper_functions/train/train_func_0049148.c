faidx_fetch_seq(const faidx_t *fai, const char *c_name, int p_beg_i, int p_end_i, int *len)
{
	int l;
	char c;
    khiter_t iter;
    faidx1_t val;
	char *seq=NULL;


    iter = kh_get(s, fai->hash, c_name);
    if(iter == kh_end(fai->hash)) return 0;
    val = kh_value(fai->hash, iter);
	if(p_end_i < p_beg_i) p_beg_i = p_end_i;
    if(p_beg_i < 0) p_beg_i = 0;
    else if(val.len <= p_beg_i) p_beg_i = val.len - 1;
    if(p_end_i < 0) p_end_i = 0;
    else if(val.len <= p_end_i) p_end_i = val.len - 1;


	int ret = bgzf_useek(fai->bgzf, val.offset + p_beg_i / val.line_blen * val.line_len + p_beg_i % val.line_blen, SEEK_SET);
    if ( ret<0 )
    {
        *len = -1;
        fprintf(stderr, "[fai_fetch_seq] Error: fai_fetch failed. (Seeking in a compressed, .gzi unindexed, file?)\n");
        return NULL;
    }
	l = 0;
	seq = (char*)malloc(p_end_i - p_beg_i + 2);
	while ( (c=bgzf_getc(fai->bgzf))>=0 && l < p_end_i - p_beg_i + 1)
		if (isgraph(c)) seq[l++] = c;
	seq[l] = '\0';
	*len = l;
	return seq;
}
