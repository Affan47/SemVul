visit_leave(ir_expression *ir)
{
   switch (ir->operation) {
   case ir_binop_sub:
      if (lowering(SUB_TO_ADD_NEG))
	 sub_to_add_neg(ir);
      break;

   case ir_binop_div:
      if (ir->operands[1]->type->is_integer() && lowering(INT_DIV_TO_MUL_RCP))
	 int_div_to_mul_rcp(ir);
      else if (ir->operands[1]->type->is_float() && lowering(DIV_TO_MUL_RCP))
	 div_to_mul_rcp(ir);
      break;

   case ir_unop_exp:
      if (lowering(EXP_TO_EXP2))
	 exp_to_exp2(ir);
      break;

   case ir_unop_log:
      if (lowering(LOG_TO_LOG2))
	 log_to_log2(ir);
      break;

   case ir_binop_mod:
      if (lowering(MOD_TO_FRACT) && ir->type->is_float())
	 mod_to_fract(ir);
      break;

   case ir_binop_pow:
      if (lowering(POW_TO_EXP2))
	 pow_to_exp2(ir);
      break;

   case ir_quadop_bitfield_insert:
      if (lowering(BITFIELD_INSERT_TO_BFM_BFI))
         bitfield_insert_to_bfm_bfi(ir);
      break;

   case ir_binop_ldexp:
      if (lowering(LDEXP_TO_ARITH))
         ldexp_to_arith(ir);
      break;

   default:
      return visit_continue;
   }

   return visit_continue;
}
