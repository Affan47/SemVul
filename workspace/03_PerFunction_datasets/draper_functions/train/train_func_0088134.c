func_random(eval_scalar *r, eval_int *p1)
{
	uint64 d = rand();
	scalar_create_int_q(r, (p1->value != 0) ? (d % p1->value):0);
	return 1;
}
