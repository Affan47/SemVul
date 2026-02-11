compileExternalFunctionArguments(ostream &CompileCode, unsigned int &instruction_number,
                                                       bool lhs_rhs, const temporary_terms_t &temporary_terms,
                                                       const map_idx_t &map_idx, bool dynamic, bool steady_dynamic,
                                                       deriv_node_temp_terms_t &tef_terms) const
{
  for (vector<expr_t>::const_iterator it = arguments.begin();
       it != arguments.end(); it++)
    (*it)->compile(CompileCode, instruction_number, lhs_rhs, temporary_terms, map_idx,
                   dynamic, steady_dynamic, tef_terms);
  return (arguments.size());
}
