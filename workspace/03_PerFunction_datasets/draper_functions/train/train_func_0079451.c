same_range (pIIR_Range r1, pIIR_Range r2)
{
  if (r1 == r2)
    return true;
  if (!r1 || !r2)
    return false;
  if (r1->kind() != r2->kind())
    return false;
  if (r1->is(IR_EXPLICIT_RANGE))
    {
      pIIR_ExplicitRange er1 = pIIR_ExplicitRange(r1);
      pIIR_ExplicitRange er2 = pIIR_ExplicitRange(r2);
      return er1->direction == er2->direction
	&& same_expr (er1->left, er2->left)
	&& same_expr (er1->right, er2->right);
    }
  else if (r1->is(IR_ARRAY_RANGE))
    {
      pIIR_ArrayRange ar1 = pIIR_ArrayRange(r1);
      pIIR_ArrayRange ar2 = pIIR_ArrayRange(r2);
      return ar1->array == ar2->array
	&& same_expr (ar1->index, ar2->index);
    }
  else
    return true;
}
