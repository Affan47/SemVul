check_cat(const struct line_cats *Cats, const int *cats, int ncats)
{
    int i;

    if (cats) {
	for (i = 0; i < Cats->n_cats; i++) {
	    if ((int *)bsearch((void *) &(Cats->cat[i]), cats, ncats, sizeof(int),
			       srch)) {

		break;
	    }
	}

	if (i == Cats->n_cats)
	    return FALSE;
    }

    return TRUE;
}
