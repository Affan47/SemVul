update_uses (df_ref *use_rec)
{
  while (*use_rec)
    {
      df_ref use = *use_rec++;
      int regno = DF_REF_REGNO (use);


      if (DF_REF_ID (use) >= (int) VEC_length (df_ref, use_def_ref))
        VEC_safe_grow_cleared (df_ref, heap, use_def_ref,
                               DF_REF_ID (use) + 1);

#ifdef ENABLE_CHECKING
      gcc_assert (sparseset_bit_p (active_defs_check, regno));
#endif
      VEC_replace (df_ref, use_def_ref, DF_REF_ID (use), active_defs[regno]);
    }
}
