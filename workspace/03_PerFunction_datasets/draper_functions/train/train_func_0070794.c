bam_plp_push(bam_plp_t iter, const bam1_t *b)
{
	if (iter->error) return -1;
	if (b) {
		if (b->core.tid < 0) return 0;
		if (b->core.flag & iter->flag_mask) return 0;
		if (iter->tid == b->core.tid && iter->pos == b->core.pos && iter->mp->cnt > iter->maxcnt) return 0;
		bam_copy1(&iter->tail->b, b);
#ifndef BAM_NO_ID
		iter->tail->b.id = iter->id++;
#endif
		iter->tail->beg = b->core.pos;
		iter->tail->end = b->core.pos + bam_cigar2rlen(b->core.n_cigar, bam_get_cigar(b));
		iter->tail->s = g_cstate_null; iter->tail->s.end = iter->tail->end - 1;
		if (b->core.tid < iter->max_tid) {
			fprintf(stderr, "[bam_pileup_core] the input is not sorted (chromosomes out of order)\n");
			iter->error = 1;
			return -1;
		}
		if ((b->core.tid == iter->max_tid) && (iter->tail->beg < iter->max_pos)) {
			fprintf(stderr, "[bam_pileup_core] the input is not sorted (reads out of order)\n");
			iter->error = 1;
			return -1;
		}
		iter->max_tid = b->core.tid; iter->max_pos = iter->tail->beg;
		if (iter->tail->end > iter->pos || iter->tail->b.core.tid > iter->tid) {
			iter->tail->next = mp_alloc(iter->mp);
			iter->tail = iter->tail->next;
		}
	} else iter->is_eof = 1;
	return 0;
}
