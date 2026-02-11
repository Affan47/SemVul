ipa_populate_param_decls (struct cgraph_node *node,
			  struct ipa_node_params *info)
{
  tree fndecl;
  tree fnargs;
  tree parm;
  int param_num;

  fndecl = node->decl;
  fnargs = DECL_ARGUMENTS (fndecl);
  param_num = 0;
  for (parm = fnargs; parm; parm = DECL_CHAIN (parm))
    {
      VEC_index (ipa_param_descriptor_t,
		 info->descriptors, param_num)->decl = parm;
      param_num++;
    }
}
