find_matching_signature(const char *name, const exec_list *actual_parameters,
			gl_shader **shader_list, unsigned num_shaders,
			bool use_builtin)
{
   for (unsigned i = 0; i < num_shaders; i++) {
      ir_function *const f = shader_list[i]->symbols->get_function(name);

      if (f == NULL)
	 continue;

      ir_function_signature *sig =
         f->matching_signature(NULL, actual_parameters);

      if ((sig == NULL) ||
          (!sig->is_defined && !sig->is_intrinsic))
	 continue;


      if (use_builtin != sig->is_builtin())
	    continue;

      return sig;
   }

   return NULL;
}
