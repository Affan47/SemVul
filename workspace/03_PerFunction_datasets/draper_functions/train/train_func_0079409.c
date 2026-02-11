vn_phi_compute_hash (vn_phi_t vp1)
{
  hashval_t result;
  int i;
  tree phi1op;
  tree type;

  result = vp1->block->index;


  type = TREE_TYPE (VEC_index (tree, vp1->phiargs, 0));
  result += (INTEGRAL_TYPE_P (type)
	     + (INTEGRAL_TYPE_P (type)
		? TYPE_PRECISION (type) + TYPE_UNSIGNED (type) : 0));

  FOR_EACH_VEC_ELT (tree, vp1->phiargs, i, phi1op)
    {
      if (phi1op == VN_TOP)
	continue;
      result = iterative_hash_expr (phi1op, result);
    }

  return result;
}
