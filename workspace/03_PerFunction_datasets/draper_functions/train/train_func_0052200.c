fsm_set_avail(Page page, int slot, uint8 value)
{
	int			nodeno = NonLeafNodesPerPage + slot;
	FSMPage		fsmpage = (FSMPage) PageGetContents(page);
	uint8		oldvalue;

	Assert(slot < LeafNodesPerPage);

	oldvalue = fsmpage->fp_nodes[nodeno];


	if (oldvalue == value && value <= fsmpage->fp_nodes[0])
		return false;

	fsmpage->fp_nodes[nodeno] = value;


	do
	{
		uint8		newvalue = 0;
		int			lchild;
		int			rchild;

		nodeno = parentof(nodeno);
		lchild = leftchild(nodeno);
		rchild = lchild + 1;

		newvalue = fsmpage->fp_nodes[lchild];
		if (rchild < NodesPerPage)
			newvalue = Max(newvalue,
						   fsmpage->fp_nodes[rchild]);

		oldvalue = fsmpage->fp_nodes[nodeno];
		if (oldvalue == newvalue)
			break;

		fsmpage->fp_nodes[nodeno] = newvalue;
	} while (nodeno > 0);


	if (value > fsmpage->fp_nodes[0])
		fsm_rebuild_page(page);

	return true;
}
