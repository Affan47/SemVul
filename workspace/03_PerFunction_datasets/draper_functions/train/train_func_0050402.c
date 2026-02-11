_copyRangeTblEntry(const RangeTblEntry *from)
{
	RangeTblEntry *newnode = makeNode(RangeTblEntry);

	COPY_SCALAR_FIELD(rtekind);
	COPY_SCALAR_FIELD(relid);
	COPY_SCALAR_FIELD(relkind);
	COPY_NODE_FIELD(tablesample);
	COPY_NODE_FIELD(subquery);
	COPY_SCALAR_FIELD(security_barrier);
	COPY_SCALAR_FIELD(jointype);
	COPY_NODE_FIELD(joinaliasvars);
	COPY_NODE_FIELD(functions);
	COPY_SCALAR_FIELD(funcordinality);
	COPY_NODE_FIELD(values_lists);
	COPY_NODE_FIELD(values_collations);
	COPY_STRING_FIELD(ctename);
	COPY_SCALAR_FIELD(ctelevelsup);
	COPY_SCALAR_FIELD(self_reference);
	COPY_NODE_FIELD(ctecoltypes);
	COPY_NODE_FIELD(ctecoltypmods);
	COPY_NODE_FIELD(ctecolcollations);
	COPY_NODE_FIELD(alias);
	COPY_NODE_FIELD(eref);
	COPY_SCALAR_FIELD(lateral);
	COPY_SCALAR_FIELD(inh);
	COPY_SCALAR_FIELD(inFromCl);
	COPY_SCALAR_FIELD(requiredPerms);
	COPY_SCALAR_FIELD(checkAsUser);
	COPY_BITMAPSET_FIELD(selectedCols);
	COPY_BITMAPSET_FIELD(insertedCols);
	COPY_BITMAPSET_FIELD(updatedCols);
	COPY_NODE_FIELD(securityQuals);

	return newnode;
}
