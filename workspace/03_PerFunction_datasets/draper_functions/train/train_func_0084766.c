vn_reference_op_compute_hash (const vn_reference_op_t vro1, hashval_t result)
{
  result = iterative_hash_hashval_t (vro1->opcode, result);
  if (vro1->op0)
    result = iterative_hash_expr (vro1->op0, result);
  if (vro1->op1)
    result = iterative_hash_expr (vro1->op1, result);
  if (vro1->op2)
    result = iterative_hash_expr (vro1->op2, result);
  return result;
}
