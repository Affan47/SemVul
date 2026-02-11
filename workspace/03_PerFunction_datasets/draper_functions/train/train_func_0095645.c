replicate_data_item (const model_data_item *orig)
{
    model_data_item *item = malloc(sizeof *item);

    if (item != NULL) {
	item->key = gretl_strdup(orig->key);
	if (item->key == NULL) {
	    free(item);
	    item = NULL;
	}
    }

    if (item != NULL) {
	if (orig->type == GRETL_TYPE_MATRIX) {
	    item->ptr = gretl_matrix_copy(orig->ptr);
	} else {
	    item->ptr = malloc(orig->size);
	}
	if (item->ptr == NULL) {
	    free(item->key);
	    free(item);
	    item = NULL;
	}
    }

    if (item != NULL) {
	if (orig->type != GRETL_TYPE_MATRIX) {
	    memcpy(item->ptr, orig->ptr, orig->size);
	}
	item->type = orig->type;
	item->size = orig->size;
	item->destructor = orig->destructor;
    }

    return item;
}
