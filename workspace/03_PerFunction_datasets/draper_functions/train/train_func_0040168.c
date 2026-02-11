isl_val_is_infty(__isl_keep isl_val *v)
{
	if (!v)
		return -1;

	return isl_int_is_pos(v->n) && isl_int_is_zero(v->d);
}
