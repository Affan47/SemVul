mpw_is_complex(mpw_ptr op)
{
	mpw_uncomplex(op);
	return MPW_IS_COMPLEX (op);
}
