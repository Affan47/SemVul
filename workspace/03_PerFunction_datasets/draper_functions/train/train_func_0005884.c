joiner_new (int nrows)
{
    joiner *jr = malloc(sizeof *jr);

    if (jr != NULL) {
	jr->rows = malloc(nrows * sizeof *jr->rows);
	if (jr->rows == NULL) {
	    free(jr);
	    jr = NULL;
	}
    }

    if (jr != NULL) {
	jr->n_rows = nrows;
	jr->n_unique = 0;
	jr->keys = NULL;
	jr->key_freq = NULL;
	jr->key_row = NULL;
	jr->l_keyno = NULL;
	jr->r_keyno = NULL;
    }

    return jr;
}
