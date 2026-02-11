sci_refcount_decref(void *data)
{
#ifdef TRACE_REFCOUNT
fprintf(stderr, "[] REF: Dec'ing %p (prev ref=%d) OK=%d\n", data, REFCOUNT(data),
	REFCOUNT_CHECK(data));
#endif
	if (!REFCOUNT_CHECK(data)) {
		BREAKPOINT();
	} else if (--REFCOUNT(data) == 0) {
		guint32 *fdata = (guint32*)data;

		fdata[-1] = REFCOUNT_MAGIC_DEAD_1;
		fdata[-3] = REFCOUNT_MAGIC_DEAD_2;

#ifdef TRACE_REFCOUNT
fprintf(stderr, "[] REF: Freeing (%p)...\n", fdata - 3);
#endif
		sci_free(fdata - 3);
#ifdef TRACE_REFCOUNT
fprintf(stderr, "[] REF: Done.\n");
#endif
	}
}
