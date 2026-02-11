mono_liveness_handle_exception_clauses (MonoCompile *cfg)
{
	MonoBasicBlock *bb;
	GSList *visited = NULL;
	MonoMethodHeader *header = cfg->header;
	MonoExceptionClause *clause, *clause2;
	int i, j;
	gboolean *outer_try;


	outer_try = (gboolean *)mono_mempool_alloc0 (cfg->mempool, sizeof (gboolean) * header->num_clauses);
	for (i = 0; i < header->num_clauses; ++i)
		outer_try [i] = TRUE;


	for (i = header->num_clauses - 1; i >= 0; --i) {
		clause = &header->clauses [i];

		if (clause->flags != 0) {
			outer_try [i] = TRUE;

			for (j = i - 1; j >= 0; --j) {
				clause2 = &header->clauses [j];

				if (clause2->flags == 0 && MONO_OFFSET_IN_HANDLER (clause, clause2->try_offset)) {
					outer_try [j] = FALSE;
					break;
				}
				if (clause2->try_offset < clause->try_offset)

					break;
			}
		}
	}


	for (bb = cfg->bb_entry; bb; bb = bb->next_bb) {

		if (bb->region == -1)
			continue;

		if (MONO_BBLOCK_IS_IN_REGION (bb, MONO_REGION_TRY) && outer_try [MONO_REGION_CLAUSE_INDEX (bb->region)])
			continue;

		if (cfg->verbose_level > 2)
			printf ("pessimize variables in bb %d.\n", bb->block_num);

		visit_bb (cfg, bb, &visited);
	}
	g_slist_free (visited);
}
