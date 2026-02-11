do_cmp_op (VerifyContext *ctx, const unsigned char table [TYPE_MAX][TYPE_MAX], guint32 opcode)
{
	ILStackDesc *a, *b;
	int idxa, idxb;
	unsigned char res;

	if (!check_underflow (ctx, 2))
		return;
	b = stack_pop (ctx);
	a = stack_pop (ctx);

	if (opcode == CEE_CGT_UN) {
		if ((stack_slot_is_reference_value (a) && stack_slot_is_null_literal (b)) ||
			(stack_slot_is_reference_value (b) && stack_slot_is_null_literal (a))) {
			stack_push_val (ctx, TYPE_I4, &mono_defaults.int32_class->byval_arg);
			return;
		}
	}

	idxa = stack_slot_get_underlying_type (a);
	if (stack_slot_is_managed_pointer (a))
		idxa = TYPE_PTR;

	idxb = stack_slot_get_underlying_type (b);
	if (stack_slot_is_managed_pointer (b))
		idxb = TYPE_PTR;

	if (stack_slot_is_complex_type_not_reference_type (a) || stack_slot_is_complex_type_not_reference_type (b)) {
		res = TYPE_INV;
	} else {
		--idxa;
		--idxb;
		res = table [idxa][idxb];
	}

	if(res == TYPE_INV) {
		char *left_type = stack_slot_full_name (a);
		char *right_type = stack_slot_full_name (b);
		CODE_NOT_VERIFIABLE (ctx, g_strdup_printf("Compare instruction applyed to ill formed stack (%s x %s) at 0x%04x", left_type, right_type, ctx->ip_offset));
		g_free (left_type);
		g_free (right_type);
	} else if (res & NON_VERIFIABLE_RESULT) {
		CODE_NOT_VERIFIABLE (ctx, g_strdup_printf ("Compare instruction is not verifiable (%s x %s) at 0x%04x", stack_slot_get_name (a), stack_slot_get_name (b), ctx->ip_offset));
 		res = res & ~NON_VERIFIABLE_RESULT;
 	}
 	stack_push_val (ctx, TYPE_I4, &mono_defaults.int32_class->byval_arg);
}
