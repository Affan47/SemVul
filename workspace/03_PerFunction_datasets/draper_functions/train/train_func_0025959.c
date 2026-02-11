compile(ostream &CompileCode, unsigned int &instruction_number,
                     bool lhs_rhs, const temporary_terms_t &temporary_terms,
                     const map_idx_t &map_idx, bool dynamic, bool steady_dynamic,
                     deriv_node_temp_terms_t &tef_terms) const
{
  temporary_terms_t::const_iterator it = temporary_terms.find(const_cast<UnaryOpNode *>(this));
  if (it != temporary_terms.end())
    {
      if (dynamic)
        {
          map_idx_t::const_iterator ii = map_idx.find(idx);
          FLDT_ fldt(ii->second);
          fldt.write(CompileCode, instruction_number);
        }
      else
        {
          map_idx_t::const_iterator ii = map_idx.find(idx);
          FLDST_ fldst(ii->second);
          fldst.write(CompileCode, instruction_number);
        }
      return;
    }
  if (op_code == oSteadyState)
    arg->compile(CompileCode, instruction_number, lhs_rhs, temporary_terms, map_idx, dynamic, true, tef_terms);
  else
    {
      arg->compile(CompileCode, instruction_number, lhs_rhs, temporary_terms, map_idx, dynamic, steady_dynamic, tef_terms);
      FUNARY_ funary(op_code);
      funary.write(CompileCode, instruction_number);
    }
}
