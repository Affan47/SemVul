emit_process_body (pIIR_ProcessStatement p, string &str, RegionStack &rstack, int l)
{
  pIIR_SequentialStatementList sl = p->process_statement_part;

  ContextInfo &ctxt = *ActiveContext(rstack);

  if (ctxt.wait_statements.size() &&
      ! p->is(IR_SENSITIZED_PROCESS_STATEMENT) &&
      ! p->is(IR_IMPLICIT_PROCESS_STATEMENT)) {
    str += "  switch (jmp) {\n";
    for(unsigned int i=1 ; i <= ctxt.wait_statements.size(); i++)
      str += "      case " + to_string(i) + ": goto lab" + to_string(i) + ";\n";
    str += "  };\n\n  lab0:\n";
  }


  if (sl != NULL)
    emit_impl(sl, str, rstack, l);


  if (ctxt.wait_statements.size() &&
      ! p->is(IR_SENSITIZED_PROCESS_STATEMENT) &&
      ! p->is(IR_IMPLICIT_PROCESS_STATEMENT)) {

    last_pos_info = emit_posinfo(p->pos, str, last_pos_info, l);
    str += spaces(l) + " goto lab0;\n";
  } else {


    str += spaces(l) + "return true;\n";
  }
}
