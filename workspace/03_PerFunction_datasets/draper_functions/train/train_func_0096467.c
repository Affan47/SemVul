add_looparound_copies (struct loop *loop, chain_p chain)
{
  unsigned i;
  dref ref, root = get_chain_root (chain);
  gimple phi;

  FOR_EACH_VEC_ELT (chain->refs, i, ref)
    {
      phi = find_looparound_phi (loop, ref, root);
      if (!phi)
	continue;

      bitmap_set_bit (looparound_phis, SSA_NAME_VERSION (PHI_RESULT (phi)));
      insert_looparound_copy (chain, ref, phi);
    }
}
