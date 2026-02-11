_vala_math_equation_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	MathEquation * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, TYPE_MATH_EQUATION, MathEquation);
	switch (property_id) {
		case MATH_EQUATION_WORD_SIZE:
		g_value_set_int (value, math_equation_get_word_size (self));
		break;
		case MATH_EQUATION_SOURCE_CURRENCY:
		g_value_take_string (value, math_equation_get_source_currency (self));
		break;
		case MATH_EQUATION_TARGET_CURRENCY:
		g_value_take_string (value, math_equation_get_target_currency (self));
		break;
		case MATH_EQUATION_SOURCE_UNITS:
		g_value_take_string (value, math_equation_get_source_units (self));
		break;
		case MATH_EQUATION_TARGET_UNITS:
		g_value_take_string (value, math_equation_get_target_units (self));
		break;
		case MATH_EQUATION_DISPLAY:
		g_value_take_string (value, math_equation_get_display (self));
		break;
		case MATH_EQUATION_IN_SOLVE:
		g_value_set_boolean (value, math_equation_get_in_solve (self));
		break;
		case MATH_EQUATION_VARIABLES:
		g_value_set_object (value, math_equation_get_variables (self));
		break;
		case MATH_EQUATION_SERIALIZER:
		g_value_set_object (value, math_equation_get_serializer (self));
		break;
		case MATH_EQUATION_ACCURACY:
		g_value_set_int (value, math_equation_get_accuracy (self));
		break;
		case MATH_EQUATION_SHOW_THOUSANDS_SEPARATORS:
		g_value_set_boolean (value, math_equation_get_show_thousands_separators (self));
		break;
		case MATH_EQUATION_SHOW_TRAILING_ZEROES:
		g_value_set_boolean (value, math_equation_get_show_trailing_zeroes (self));
		break;
		case MATH_EQUATION_NUMBER_FORMAT:
		g_value_set_enum (value, math_equation_get_number_format (self));
		break;
		case MATH_EQUATION_NUMBER_BASE:
		g_value_set_int (value, math_equation_get_number_base (self));
		break;
		case MATH_EQUATION_ANGLE_UNITS:
		g_value_set_enum (value, math_equation_get_angle_units (self));
		break;
		case MATH_EQUATION_STATUS:
		g_value_take_string (value, math_equation_get_status (self));
		break;
		case MATH_EQUATION_ERROR_TOKEN_START:
		g_value_set_uint (value, math_equation_get_error_token_start (self));
		break;
		case MATH_EQUATION_ERROR_TOKEN_END:
		g_value_set_uint (value, math_equation_get_error_token_end (self));
		break;
		case MATH_EQUATION_IS_EMPTY:
		g_value_set_boolean (value, math_equation_get_is_empty (self));
		break;
		case MATH_EQUATION_IS_RESULT:
		g_value_set_boolean (value, math_equation_get_is_result (self));
		break;
		case MATH_EQUATION_EQUATION:
		g_value_take_string (value, math_equation_get_equation (self));
		break;
		case MATH_EQUATION_NUMBER:
		value_take_number (value, math_equation_get_number (self));
		break;
		case MATH_EQUATION_NUMBER_MODE:
		g_value_set_enum (value, math_equation_get_number_mode (self));
		break;
		case MATH_EQUATION_ANSWER:
		value_set_number (value, math_equation_get_answer (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
