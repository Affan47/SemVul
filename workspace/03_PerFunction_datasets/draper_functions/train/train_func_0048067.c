store_history(ObjectStream &s)
{
	uint count = sizeof hist_atoms / sizeof hist_atoms[0];
	PUT_INT32D(s, count);
	for (uint i=0; i < count; i++) {
		putIDComment(s, hist_atoms[i]);
		PUTX_INT32X(s, hist_atoms[i], "atom");
		List *c = (List*)getAtomValue(hist_atoms[i]);
		PUTX_OBJECT(s, c, "list");
	}
}
