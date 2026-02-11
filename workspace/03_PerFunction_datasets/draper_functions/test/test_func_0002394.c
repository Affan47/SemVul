update_uses (df_ref *use_rec)
{
  while (*use_rec)
    {
      df_ref use = *use_rec++;
      int regno = DF_REF_REGNO (use);


      if (DF_REF_ID (use) >= (int) use_def_ref.length ())
        use_def_ref.safe_grow_cleared (DF_REF_ID (use) + 1);

#ifdef ENABLE_CHECKING
      gcc_assert (sparseset_bit_p (active_defs_check, regno));
#endif
      use_def_ref[DF_REF_ID (use)] = active_defs[regno];
    }
}
