vardef_end () {

  if (variantDefs[lastVariantDef].name) {
    register int i;
    for (i = 0; cmd_line_vars[i] && (i < MAXCMDLINEVARS); i++) {
      if (strcmp (cmd_line_vars[i]+1, variantDefs[lastVariantDef].name))
	continue;
      activate_variant (cmd_line_vars[i]);
    }
  }
}
