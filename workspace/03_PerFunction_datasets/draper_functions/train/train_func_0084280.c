_outConst(StringInfo str, Const *node)
{
	WRITE_NODE_TYPE("CONST");

	WRITE_OID_FIELD(consttype);
	WRITE_INT_FIELD(consttypmod);
	WRITE_INT_FIELD(constlen);
	WRITE_BOOL_FIELD(constbyval);
	WRITE_BOOL_FIELD(constisnull);

	appendStringInfo(str, " :constvalue ");
	if (node->constisnull)
		appendStringInfo(str, "<>");
	else
		_outDatum(str, node->constvalue, node->constlen, node->constbyval);
}
