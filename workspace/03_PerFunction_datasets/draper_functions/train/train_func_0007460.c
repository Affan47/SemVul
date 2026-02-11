copy_model_data_items (MODEL *targ, const MODEL *src)
{
    int i, n = src->n_data_items;
    int err = 0;

    targ->data_items = malloc(n * sizeof *targ->data_items);
    if (targ->data_items == NULL) {
	return 1;
    }

    for (i=0; i<n; i++) {
	targ->data_items[i] = NULL;
    }

    for (i=0; i<n; i++) {
	targ->data_items[i] = replicate_data_item(src->data_items[i]);
	if (targ->data_items[i] == NULL) {
	    err = 1;
	    break;
	}
    }

    if (err) {
	for (i=0; i<n; i++) {
	    free(targ->data_items[i]);
	}
	free(targ->data_items);
	targ->data_items = NULL;
	targ->n_data_items = 0;
    } else {
	targ->n_data_items = n;
    }

    return err;
}
