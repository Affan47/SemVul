destroy_restriction_set (gretl_restriction *rset)
{
    if (rset->rows != NULL) {
	int i;

	for (i=0; i<rset->g; i++) {
	    destroy_restriction(rset->rows[i]);
	}
	free(rset->rows);
    }

    free(rset->mask);

#if RDEBUG
    fprintf(stderr, "destroy_restriction_set: R at %p, q at %p\n",
	    (void *) rset->R, (void *) rset->q);
    fprintf(stderr, " Ra at %p, qa at %p\n",
	    (void *) rset->Ra, (void *) rset->qa);
#endif

    gretl_matrix_free(rset->R);
    gretl_matrix_free(rset->q);
    gretl_matrix_free(rset->Ra);
    gretl_matrix_free(rset->qa);

    free(rset->rfunc);

    free(rset);
}
