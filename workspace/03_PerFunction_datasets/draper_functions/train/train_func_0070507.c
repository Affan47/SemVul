func_fmax(eval_scalar *r, eval_float *p1, eval_float *p2)
{
	r->type=SCALAR_FLOAT;
	r->scalar.floatnum.value=(p1->value>p2->value) ? p1->value : p2->value;
	return 1;
}
