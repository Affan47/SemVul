copy_to_reference_missmask (const char *mask)
{
    if (refmask != NULL) {
	free(refmask);
	refmask = NULL;
    }

    refmask = gretl_strdup(mask);

#if MASKDEBUG
    fprintf(stderr, "copy_to_reference_missmask: refmask = %p\n",
	    (void *) refmask);
#endif

    return (refmask == NULL)? E_ALLOC : 0;
}
