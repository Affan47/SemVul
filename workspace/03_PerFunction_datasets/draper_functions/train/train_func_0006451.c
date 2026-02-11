gle_memory_cell_equals(GLEMemoryCell* a, GLEMemoryCell* b) {
	if (a->Type != b->Type) return false;
	switch (a->Type) {
		case GLE_MC_UNKNOWN:
			return true;
		case GLE_MC_BOOL:
			return a->Entry.BoolVal == b->Entry.BoolVal;
		case GLE_MC_INT:
			return a->Entry.IntVal == b->Entry.IntVal;
		case GLE_MC_DOUBLE:
			return a->Entry.DoubleVal == b->Entry.DoubleVal;
		case GLE_MC_OBJECT:
			return a->Entry.ObjectVal->equals(b->Entry.ObjectVal);
	}
	return false;
}
