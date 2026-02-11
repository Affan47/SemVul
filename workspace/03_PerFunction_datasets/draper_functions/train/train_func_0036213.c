make_operand_mod_oneline_iteration(Block *bpt, Write_sharing *ws,
				   Quadruple *do_qr, Operand *buf_op)
{
    SemanticNode *node;
    SemTree *tree;
    int cache_line_size = 32;
    int elem_size = get_elem_size_from_ws(bpt, ws);
    Quadruple *new_qr, *first_qr, *qr;
    Operand *new_op, *op = buf_op->inner;

    node = ConstructSemTree(do_qr, op);
    tree = semnode2semtree(node, bpt->module);
    tree = concat_semtree(OPE_MOD, tree,
			  make_semtree_const_int(cache_line_size / elem_size));
    node = semtree2semnode(tree);
    new_qr = ConvertSemTree2Qr(bpt->module, node, &new_op);

    if (new_qr != NULL) {
	for (qr = new_qr; qr != NULL; qr = qr->prev) {
	    qr->stm = do_qr->stm;
	    first_qr = qr;
	}
    }


    buf_op->inner = copy_operand(new_op);
    return first_qr;
}
