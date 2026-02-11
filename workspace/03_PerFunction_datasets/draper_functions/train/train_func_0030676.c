augment_vecm_restriction (gretl_restriction *rset,
				     char letter)
{
    GRETL_VAR *vecm = rset->obj;
    const gretl_matrix *R0, *q0;
    gretl_matrix *R2 = NULL, *q2 = NULL;
    int err = 0;

    if (letter == 'b') {
	R0 = gretl_VECM_R_matrix(vecm);
	q0 = gretl_VECM_q_matrix(vecm);
    } else {
	R0 = gretl_VECM_Ra_matrix(vecm);
	q0 = gretl_VECM_qa_matrix(vecm);
    }

    R2 = gretl_matrix_row_concat(R0, rset->R, &err);
    if (err) {
	return err;
    }

    err = check_R_matrix(R2);
    if (err) {
	gretl_matrix_free(R2);
	return err;
    }

    if (q0 == NULL) {
	q2 = gretl_column_vector_alloc(R2->rows);
	if (q2 == NULL) {
	    err = E_ALLOC;
	} else {
	    int i, n = R0->rows;

	    for (i=0; i<R2->rows; i++) {
		q2->val[i] = (i < n)? 0.0 : rset->q->val[i-n];
	    }
	}
    } else {
	q2 = gretl_matrix_row_concat(q0, rset->q, &err);
    }

    if (err) {
	gretl_matrix_free(R2);
    } else if (letter == 'b') {
	gretl_matrix_replace(&rset->R, R2);
	gretl_matrix_replace(&rset->q, q2);
    } else {
	gretl_matrix_replace(&rset->Ra, R2);
	gretl_matrix_replace(&rset->qa, q2);
    }

    return err;
}
