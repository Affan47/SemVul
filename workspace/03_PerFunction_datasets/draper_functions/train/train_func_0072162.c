pat_ref_lookup(const char *reference)
{
	struct pat_ref *ref;

	list_for_each_entry(ref, &pattern_reference, list)
		if (ref->reference && strcmp(reference, ref->reference) == 0)
			return ref;
	return NULL;
}
