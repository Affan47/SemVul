init_pragma (void)
{
  if (flag_openmp)
    {
      const int n_omp_pragmas = sizeof (omp_pragmas) / sizeof (*omp_pragmas);
      int i;

      for (i = 0; i < n_omp_pragmas; ++i)
	cpp_register_deferred_pragma (parse_in, "omp", omp_pragmas[i].name,
				      omp_pragmas[i].id, true, true);
    }

  if (!flag_preprocess_only)
    cpp_register_deferred_pragma (parse_in, "GCC", "pch_preprocess",
				  PRAGMA_GCC_PCH_PREPROCESS, false, false);

#ifdef HANDLE_PRAGMA_PACK_WITH_EXPANSION
  c_register_pragma_with_expansion (0, "pack", handle_pragma_pack);
#else
  c_register_pragma (0, "pack", handle_pragma_pack);
#endif
  c_register_pragma (0, "weak", handle_pragma_weak);
  c_register_pragma ("GCC", "visibility", handle_pragma_visibility);

  c_register_pragma ("GCC", "diagnostic", handle_pragma_diagnostic);
  c_register_pragma ("GCC", "target", handle_pragma_target);
  c_register_pragma ("GCC", "optimize", handle_pragma_optimize);
  c_register_pragma ("GCC", "push_options", handle_pragma_push_options);
  c_register_pragma ("GCC", "pop_options", handle_pragma_pop_options);
  c_register_pragma ("GCC", "reset_options", handle_pragma_reset_options);

  c_register_pragma ("STDC", "FLOAT_CONST_DECIMAL64",
		     handle_pragma_float_const_decimal64);

  c_register_pragma_with_expansion (0, "redefine_extname",
				    handle_pragma_redefine_extname);
  c_register_pragma (0, "extern_prefix", handle_pragma_extern_prefix);

  c_register_pragma_with_expansion (0, "message", handle_pragma_message);

#ifdef REGISTER_TARGET_PRAGMAS
  REGISTER_TARGET_PRAGMAS ();
#endif


  invoke_plugin_callbacks (PLUGIN_PRAGMAS, NULL);
}
