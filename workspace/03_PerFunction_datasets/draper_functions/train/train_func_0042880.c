get_type(enum ECPGttype type)
{
	switch (type)
	{
		case ECPGt_char:
			return ("ECPGt_char");
			break;
		case ECPGt_unsigned_char:
			return ("ECPGt_unsigned_char");
			break;
		case ECPGt_short:
			return ("ECPGt_short");
			break;
		case ECPGt_unsigned_short:
			return ("ECPGt_unsigned_short");
			break;
		case ECPGt_int:
			return ("ECPGt_int");
			break;
		case ECPGt_unsigned_int:
			return ("ECPGt_unsigned_int");
			break;
		case ECPGt_long:
			return ("ECPGt_long");
			break;
		case ECPGt_unsigned_long:
			return ("ECPGt_unsigned_long");
			break;
		case ECPGt_long_long:
			return ("ECPGt_long_long");
			break;
		case ECPGt_unsigned_long_long:
			return ("ECPGt_unsigned_long_long");
			break;
		case ECPGt_float:
			return ("ECPGt_float");
			break;
		case ECPGt_double:
			return ("ECPGt_double");
			break;
		case ECPGt_bool:
			return ("ECPGt_bool");
			break;
		case ECPGt_varchar:
			return ("ECPGt_varchar");
		case ECPGt_NO_INDICATOR:
			return ("ECPGt_NO_INDICATOR");
			break;
		case ECPGt_char_variable:
			return ("ECPGt_char_variable");
			break;
		case ECPGt_const:
			return ("ECPGt_const");
			break;
		case ECPGt_decimal:
			return ("ECPGt_decimal");
			break;
		case ECPGt_numeric:
			return ("ECPGt_numeric");
			break;
		case ECPGt_interval:
			return ("ECPGt_interval");
			break;
		case ECPGt_descriptor:
			return ("ECPGt_descriptor");
			break;
		case ECPGt_date:
			return ("ECPGt_date");
			break;
		case ECPGt_timestamp:
			return ("ECPGt_timestamp");
			break;
		default:
			mmerror(PARSE_ERROR, ET_ERROR, "unrecognized variable type code %d", type);
	}

	return NULL;
}
