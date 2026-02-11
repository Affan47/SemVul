php_array_natural_general_compare(const void *a, const void *b, int fold_case)
{
	Bucket *f, *s;
	zval *fval, *sval;
	zval first, second;
	int result;

	f = *((Bucket **) a);
	s = *((Bucket **) b);

	fval = *((zval **) f->pData);
	sval = *((zval **) s->pData);
	first = *fval;
	second = *sval;

	if (Z_TYPE_P(fval) != IS_STRING) {
		zval_copy_ctor(&first);
		convert_to_string(&first);
	}

	if (Z_TYPE_P(sval) != IS_STRING) {
		zval_copy_ctor(&second);
		convert_to_string(&second);
	}

	result = strnatcmp_ex(Z_STRVAL(first), Z_STRLEN(first), Z_STRVAL(second), Z_STRLEN(second), fold_case);

	if (Z_TYPE_P(fval) != IS_STRING) {
		zval_dtor(&first);
	}

	if (Z_TYPE_P(sval) != IS_STRING) {
		zval_dtor(&second);
	}

	return result;
}
