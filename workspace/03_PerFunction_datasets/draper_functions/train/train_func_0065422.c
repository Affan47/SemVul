mdb_get_colbacktype_string(const MdbColumn *col)
{
	const MdbBackendType *type = mdb_get_colbacktype(col);
	if (!type) {

		static char buf[16];
		snprintf(buf,sizeof(buf), "type %04x", col->col_type);
		return buf;
	}
	return type->name;
}
