_readConst(void)
{
	READ_LOCALS(Const);

	READ_OID_FIELD(consttype);
	READ_INT_FIELD(constlen);
	READ_BOOL_FIELD(constbyval);
	READ_BOOL_FIELD(constisnull);

	token = pg_strtok(&length);
	if (local_node->constisnull)
		token = pg_strtok(&length);
	else
		local_node->constvalue = readDatum(local_node->constbyval);

	READ_DONE();
}
