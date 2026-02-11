vn_phi_insert (gimple phi, tree result)
{
  void **slot;
  vn_phi_t vp1 = (vn_phi_t) pool_alloc (current_info->phis_pool);
  unsigned i;
  VEC (tree, heap) *args = NULL;


  for (i = 0; i < gimple_phi_num_args (phi); i++)
    {
      tree def = PHI_ARG_DEF (phi, i);
      def = TREE_CODE (def) == SSA_NAME ? SSA_VAL (def) : def;
      VEC_safe_push (tree, heap, args, def);
    }
  vp1->value_id = VN_INFO (result)->value_id;
  vp1->phiargs = args;
  vp1->block = gimple_bb (phi);
  vp1->result = result;
  vp1->hashcode = vn_phi_compute_hash (vp1);

  slot = htab_find_slot_with_hash (current_info->phis, vp1, vp1->hashcode,
				   INSERT);


  *slot = vp1;
  return vp1;
}
