nodeCompare(node_ *r, nodeIndex_ *index)
{
	ReturnErrIf(r == NULL);
	ReturnErrIf(index == NULL);

	if((r->col == index->col) && (r->row == index->row)) {
		return LIST_FIND_MATCH;
	}
	return LIST_FIND_NOTAMATCH;
}
