H5Z_xform_eval_full(H5Z_node *tree, const size_t array_size,  const hid_t array_type, H5Z_result *res)
{
    H5Z_result resl, resr;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(tree);

    HDmemset(&resl, 0, sizeof(H5Z_result));
    HDmemset(&resr, 0, sizeof(H5Z_result));

    if (tree->type == H5Z_XFORM_INTEGER) {
	res->type = H5Z_XFORM_INTEGER;
	res->value.int_val = tree->value.int_val;
    }
    else if (tree->type == H5Z_XFORM_FLOAT) {
	res->type = H5Z_XFORM_FLOAT;
	res->value.float_val = tree->value.float_val;
    }
    else if (tree->type == H5Z_XFORM_SYMBOL) {
	res->type = H5Z_XFORM_SYMBOL;


	res->value.dat_val = *((void**)(tree->value.dat_val));
    }
    else {
	if(tree->lchild && H5Z_xform_eval_full(tree->lchild, array_size, array_type, &resl) < 0)
	    HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "error while performing data transform")
	if(H5Z_xform_eval_full(tree->rchild, array_size, array_type, &resr) < 0)
	    HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "error while performing data transform")

	res->type = H5Z_XFORM_SYMBOL;


	switch (tree->type) {
	    case H5Z_XFORM_PLUS:
	 	H5Z_XFORM_TYPE_OP(resl, resr, array_type, +, array_size)
		break;

	    case H5Z_XFORM_MINUS:
	 	H5Z_XFORM_TYPE_OP(resl, resr, array_type, -, array_size)
		break;

	    case H5Z_XFORM_MULT:
		H5Z_XFORM_TYPE_OP(resl, resr, array_type, *, array_size)
		break;

	    case H5Z_XFORM_DIVIDE:
	 	H5Z_XFORM_TYPE_OP(resl, resr, array_type, /, array_size)
		break;

	    default:
		HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "Invalid expression tree")
	}


	if(resl.type ==  H5Z_XFORM_SYMBOL)
	    res->value.dat_val = resl.value.dat_val;
	else if(resr.type == H5Z_XFORM_SYMBOL)
	    res->value.dat_val = resr.value.dat_val;
	else
	    HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "error during transform evaluation")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
