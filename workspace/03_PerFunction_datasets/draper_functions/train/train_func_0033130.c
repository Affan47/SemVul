gle_memory_cell_to_double(GLEMemoryCell* a, double* result) {
	switch (a->Type) {
		case GLE_MC_BOOL:
			*result = a->Entry.BoolVal ? 1.0 : 0.0;
			return true;
		case GLE_MC_INT:
			*result = a->Entry.IntVal;
			return true;
		case GLE_MC_DOUBLE:
			*result = a->Entry.DoubleVal;
			return true;
		default:
			*result = 0.0;
			return false;
	}
}
