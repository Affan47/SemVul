cast_value_dnum(PHP_VALUE_NODE *val)
{
	switch(val->type) {
		case PHP_VAL_NONE: val->int_val = 0; break;
		case PHP_VAL_BOOL:
		case PHP_VAL_INT: break;
		case PHP_VAL_FLOAT: val->int_val = (int)val->float_val; break;
		case PHP_VAL_STRING: {
			char *str = val->str_val;
			val->int_val = atoll(val->str_val);
			free(str);
			break;
		}
		case PHP_VAL_ARRAY:
		case PHP_VAL_OBJECT: val->int_val = 0; break;
		case PHP_VAL_VAR_NODE:
		case PHP_VAL_INT_DATA: assert(0); break;
	}
	val->type = PHP_VAL_INT;
}
