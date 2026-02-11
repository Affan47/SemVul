GC_clear_togglerefs ()
{
	int i;
	for (i = 0; i < GC_toggleref_array_size; ++i) {
		if (GC_toggleref_array [i].weak_ref) {
			GC_PTR object = REVEAL_POINTER (GC_toggleref_array [i].weak_ref);

			if (!GC_is_marked (object)) {
				GC_toggleref_array [i].weak_ref = (GC_hidden_pointer)NULL;
			} else {

			}
		}
	}
}
