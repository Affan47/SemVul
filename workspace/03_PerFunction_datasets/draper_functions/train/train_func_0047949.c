scalar_op(eval_scalar *xr, eval_scalar *xa, eval_scalar *xb, int op)
{
	int r;
	if ((xa->type==SCALAR_FLOAT) || (xb->type==SCALAR_FLOAT)) {
		r=scalar_float_op(xr, xa, xb, op);
	} else {
		r=scalar_int_op(xr, xa, xb, op);
	}
	scalar_destroy(xa);
	scalar_destroy(xb);
	return r;
}
