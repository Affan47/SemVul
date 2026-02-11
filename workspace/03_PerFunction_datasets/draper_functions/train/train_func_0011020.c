find_described_verb(Objid oid, Var desc)
{
    if (desc.type == TYPE_INT)
	return db_find_indexed_verb(oid, desc.v.num);
    else {
	int flag = server_flag_option("support_numeric_verbname_strings", 0);

	return db_find_defined_verb(oid, desc.v.str, flag);
    }
}
