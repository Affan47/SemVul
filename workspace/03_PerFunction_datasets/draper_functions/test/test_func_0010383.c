bam_index_destroy(bam_index_t *idx)
{
	khint_t k;
	int i;
	if (idx == 0) return;
	for (i = 0; i < idx->n; ++i) {
		khash_t(i) *index = idx->index[i];
		bam_lidx_t *index2 = idx->index2 + i;
		for (k = kh_begin(index); k != kh_end(index); ++k) {
			if (kh_exist(index, k))
				free(kh_value(index, k).list);
		}
		kh_destroy(i, index);
		free(index2->offset);
	}
	free(idx->index); free(idx->index2);
	free(idx);
}
