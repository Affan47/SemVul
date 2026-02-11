cx_logging_get_value(cx_logging_arg_type_t val_type, char *arg,
		     cx_logging_value_t * value)
{
	int val;

	value->val_type = val_type;
	switch (val_type) {
	case Cx_Logging_Arg_Value_Scalar:
		 val = strtol(arg, NULL, 10);
		 value->val.scalar[0] = val & 0xff;
		 value->val.scalar[1] = ((val >> 8) & 0xff);
		 value->val.scalar[2] = ((val >> 16) & 0xff);
		 value->val.scalar[3] = ((val >> 24) & 0xff);
		 value->val_len = 4;
		 break;
	case Cx_Logging_Arg_Value_String:
		 strncpy(value->val.string, arg, MAX_VAL_STRING);
		 value->val_len = strlen(value->val.string);
		 break;
	default:
		 return -1;
		 break;
	};
	return 0;
}
