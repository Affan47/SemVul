globaltypesize(uint16_t id)
{
    const struct cli_bc_type *ty;
    if (id <= 64)
	return (id + 7)/8;
    if (id < 69)
	return 8;
    ty = &cli_apicall_types[id - 69];
    switch (ty->kind) {
	case DArrayType:
	    return ty->numElements*globaltypesize(ty->containedTypes[0]);
	case DStructType:
	case DPackedStructType:
	    {
		unsigned i, s = 0;
		for (i=0;i<ty->numElements;i++)
		    s += globaltypesize(ty->containedTypes[i]);
		return s;
	    }
	default:
	    return 0;
    }
}
