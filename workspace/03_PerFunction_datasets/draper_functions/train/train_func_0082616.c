gretl_matrix_copy_info (gretl_matrix *targ,
				   const gretl_matrix *src)
{
    int err = 0;

    if (is_block_matrix(targ) || is_block_matrix(src)) {
	return E_DATA;
    }

    if (src->info == NULL) {
	if (targ->info != NULL) {
	    gretl_matrix_destroy_info(targ);
	}
	return 0;
    }

    if (targ->info == NULL) {
	targ->info = malloc(sizeof *targ->info);
    } else {
	strings_array_free(targ->info->colnames, targ->cols);
	strings_array_free(targ->info->rownames, targ->rows);
    }

    if (targ->info == NULL) {
	err = E_ALLOC;
    } else {
	targ->info->t1 = src->info->t1;
	targ->info->t2 = src->info->t2;
	targ->info->colnames = NULL;
	targ->info->rownames = NULL;
	if (src->info->colnames != NULL) {
	    targ->info->colnames = strings_array_dup(src->info->colnames,
						     src->cols);
	    if (targ->info->colnames == NULL) {
		err = E_ALLOC;
	    }
	}
	if (!err && src->info->rownames != NULL) {
	    targ->info->rownames = strings_array_dup(src->info->rownames,
						     src->rows);
	    if (targ->info->rownames == NULL) {
		err = E_ALLOC;
	    }
	}
    }

    return err;
}
