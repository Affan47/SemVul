m_cdfg_emit_impl (pIIR_SubprogramDeclaration sbp, string &str, RegionStack &rstack, int l)
{
  rstack.push(sbp);
  ContextInfo &ctxt = *ActiveContext(rstack);

  str += spaces(l) + "(define-procedure " + get_escaped_string(get_long_name(sbp), ":\"\\()") + " (current-scope procedure-name)\n";


  list<AccessDescriptor> objects =
    filter_unique(ctxt.accessed_objects, ACCESS,
		  tree_kind_list() <<
		  IR_SIGNAL_DECLARATION <<
		  IR_SIGNAL_INTERFACE_DECLARATION <<
		  IR_CONSTANT_DECLARATION <<
		  IR_CONSTANT_INTERFACE_DECLARATION <<
		  IR_VARIABLE_DECLARATION <<
		  IR_SHARED_VARIABLE_DECLARATION);

  if (objects.begin() != objects.end()) {
    str += spaces(l+4) + "(let* (\n";
    for (list<AccessDescriptor>::iterator i = objects.begin(); i != objects.end(); i++)
      str += spaces(l+7) + "(" + qid((*i).declaration, rstack, id_type(DEFAULT, NO_PREFIX)) +
	" (map-object current-scope procedure-name " +
	+ "\"" + get_escaped_string(get_long_name((*i).declaration)) + "\"))\n";
    str += spaces(l+7) + ")\n";
  }

  str += spaces(l+6) + "(create-procedure-statements procedure-name)\n";

  list<pIIR_Declaration> subprograms =
    filter_unique(extended_declarations(sbp),
		  tree_kind_list() <<
		  IR_PROCEDURE_DECLARATION <<
		  IR_FUNCTION_DECLARATION
		  );
  for (list<pIIR_Declaration>::iterator i = subprograms.begin(); i != subprograms.end(); i++)
    cdfg_emit_impl((*i), str, rstack, 6);


  if (sbp->subprogram_body != NULL)
    cdfg_emit_impl(sbp->subprogram_body, str, rstack, l+6);

  str += spaces(l+6) + "(create-end-procedure-statements)\n";

  str += spaces(l+4) + ")\n";

  str += spaces(l) + ")\n";


  rstack.pop();
}
