xact_desc_commit(StringInfo buf, xl_xact_commit *xlrec)
{
	int			i;

	appendStringInfoString(buf, timestamptz_to_str(xlrec->xact_time));
	if (xlrec->nrels > 0)
	{
		appendStringInfo(buf, "; rels:");
		for (i = 0; i < xlrec->nrels; i++)
		{
			RelFileNode rnode = xlrec->xnodes[i];

			appendStringInfo(buf, " %u/%u/%u",
							 rnode.spcNode, rnode.dbNode, rnode.relNode);
		}
	}
	if (xlrec->nsubxacts > 0)
	{
		TransactionId *xacts = (TransactionId *)
		&xlrec->xnodes[xlrec->nrels];

		appendStringInfo(buf, "; subxacts:");
		for (i = 0; i < xlrec->nsubxacts; i++)
			appendStringInfo(buf, " %u", xacts[i]);
	}
}
