value_cmp (void const *ptr_a, void const *ptr_b)
{
	GnmValue const *a = *(GnmValue const **)ptr_a;
	GnmValue const *b = *(GnmValue const **)ptr_b;
	switch (value_compare_real (a, b, TRUE, TRUE)) {
	case IS_EQUAL :   return  0;
	case IS_LESS :    return -1;
	case IS_GREATER : return  1;
	default :
		break;
	}
	return a->type - b->type;
}
