eel_op_sub(int argc, struct eel_data_t *argv)
{
	eel_data_t *left = argv, *right = argv + 1;
	DBG(log_printf(DLOG, "sub ");)
	if(argc != 2)
	{
		eel_error("Operator needs exactly two arguments!");
		return -1;
	}
	switch(promote(left, right))
	{
	  case EDT_REAL:
		DBG(log_printf(DLOG, "%f, %f\n", left->value.r, right->value.r);)
		left->value.r -= right->value.r;
		break;
	  case EDT_INTEGER:
		DBG(log_printf(DLOG, "%d, %d\n", left->value.i, right->value.i);)
		left->value.i -= right->value.i;
		break;
	  default:
		return -1;
	}
	return 0;
}
