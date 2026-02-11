simplify_gen_binary (enum rtx_code code, enum machine_mode mode, rtx op0,
		     rtx op1)
{
  rtx tem;


  tem = simplify_binary_operation (code, mode, op0, op1);
  if (tem)
    return tem;


  if (GET_RTX_CLASS (code) == RTX_COMM_ARITH
      && swap_commutative_operands_p (op0, op1))
    tem = op0, op0 = op1, op1 = tem;

  return gen_rtx_fmt_ee (code, mode, op0, op1);
}
