get_matrix_size (gretl_matrix *a, gretl_matrix *b,
			    int *r, int *c)
{
    int err = 0;


    if (a != NULL) {
	*r = a->rows;
	*c = b->cols;
	if (b != NULL && (b->rows != *r || b->cols != *c)) {
	    err = E_NONCONF;
	}
    } else if (b != NULL) {
	*r = b->rows;
	*c = b->cols;
    } else {
	*r = *c = 0;
    }

    return err;
}
