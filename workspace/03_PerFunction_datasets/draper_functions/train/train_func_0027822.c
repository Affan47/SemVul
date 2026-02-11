trace_type_stash (trace_type_t *tptr)
{
	trace_type_t **vec;
	int delta;
	if (trace_type_max <= tptr -> index) {
		delta = tptr -> index - trace_type_max + 10;
		vec = dmalloc (((trace_type_max + delta) *
				sizeof (trace_type_t *)), MDL);
		if (!vec)
			return;
		memset (&vec [trace_type_max], 0,
			(sizeof (trace_type_t *)) * delta);
		trace_type_max += delta;
		if (trace_types) {
		    memcpy (vec, trace_types,
			    trace_type_count * sizeof (trace_type_t *));
		    dfree (trace_types, MDL);
		}
		trace_types = vec;
	}
	trace_types [tptr -> index] = tptr;
	if (tptr -> index >= trace_type_count)
		trace_type_count = tptr -> index + 1;
}
