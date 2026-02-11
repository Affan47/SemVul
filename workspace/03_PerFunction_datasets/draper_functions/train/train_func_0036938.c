maybe_free_full_dataset (const DATASET *dset)
{
    if (dset == peerset) {
	if (fullset != NULL) {
#if SUBDEBUG
	    fprintf(stderr, "maybe_free_full_dataset: freeing fullset at %p (Z at %p)\n",
		    (void *) fullset, (void *) fullset->Z);
#endif
	    if (fullset->Z != NULL) {
		free_Z(fullset);
	    }
	    clear_datainfo(fullset, CLEAR_SUBSAMPLE);
	    free(fullset);
	    fullset = NULL;
	}
	peerset = NULL;
    }
}
