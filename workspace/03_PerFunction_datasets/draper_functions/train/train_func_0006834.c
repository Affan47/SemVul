bt_float_declaration_new(size_t mantissa_len,
		       size_t exp_len, int byte_order, size_t alignment)
{
	struct declaration_float *float_declaration;
	struct bt_declaration *declaration;

	float_declaration = g_new(struct declaration_float, 1);
	declaration = &float_declaration->p;
	declaration->id = CTF_TYPE_FLOAT;
	declaration->alignment = alignment;
	declaration->declaration_free = _float_declaration_free;
	declaration->definition_new = _float_definition_new;
	declaration->definition_free = _float_definition_free;
	declaration->ref = 1;
	float_declaration->byte_order = byte_order;

	float_declaration->sign = bt_integer_declaration_new(1,
						byte_order, false, 1, 2,
						CTF_STRING_NONE, NULL);
	float_declaration->mantissa = bt_integer_declaration_new(mantissa_len - 1,
						byte_order, false, 1, 10,
						CTF_STRING_NONE, NULL);
	float_declaration->exp = bt_integer_declaration_new(exp_len,
						byte_order, true, 1, 10,
						CTF_STRING_NONE, NULL);
	return float_declaration;
}
