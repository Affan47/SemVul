nv_pair_free_value(nv_pair_t *nvp)
{
	nv_pair_check(nvp);
	g_assert(nvp->value != NULL);

	if (nvp->allocated) {
		HFREE_NULL(nvp->value);
	} else if (nvp->value_free != NULL) {
		(*nvp->value_free)(nvp->value, nvp->length);
	}

	nvp->value = NULL;
	nvp->length = 0;
	nvp->allocated = FALSE;
}
