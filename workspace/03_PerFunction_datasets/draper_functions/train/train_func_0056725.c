bam_plp_destroy(bam_plp_t iter)
{
	mp_free(iter->mp, iter->dummy);
	mp_free(iter->mp, iter->head);
	if (iter->mp->cnt != 0)
		fprintf(stderr, "[bam_plp_destroy] memory leak: %d. Continue anyway.\n", iter->mp->cnt);
	mp_destroy(iter->mp);
	if (iter->b) bam_destroy1(iter->b);
	free(iter->plp);
	free(iter);
}
