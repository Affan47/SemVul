kdtree_get_data(const kdtree_t* kd, int i) {
	switch (kdtree_datatype(kd)) {
	case KDT_DATA_DOUBLE:
		return kd->data.d + kd->ndim * i;
	case KDT_DATA_FLOAT:
		return kd->data.f + kd->ndim * i;
	case KDT_DATA_U32:
		return kd->data.u + kd->ndim * i;
	case KDT_DATA_U16:
		return kd->data.s + kd->ndim * i;
	default:
		ERROR("kdtree_get_data: invalid data type %i", kdtree_datatype(kd));
		return NULL;
	}
}
