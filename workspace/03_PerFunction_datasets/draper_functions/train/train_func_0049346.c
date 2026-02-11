cram_add_base(cram_fd *fd, cram_container *c,
			 cram_slice *s, cram_record *r,
			 int pos, char base, char qual) {
    cram_feature f;
    f.B.pos = pos+1;
    f.B.code = 'B';
    f.B.base = base;
    f.B.qual = qual;
#ifdef BA_external
    s->BA_len++;
#else
    cram_stats_add(c->BA_stats, base);
#endif
    cram_stats_add(c->QS_stats, qual);
    BLOCK_APPEND_CHAR(s->qual_blk, qual);
    return cram_add_feature(c, s, r, &f);
}
