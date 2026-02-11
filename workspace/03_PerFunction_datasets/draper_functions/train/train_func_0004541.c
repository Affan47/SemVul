compile(ostream &CompileCode, unsigned int &instruction_number,
                      bool lhs_rhs, const temporary_terms_t &temporary_terms,
                      const map_idx_t &map_idx, bool dynamic, bool steady_dynamic,
                      deriv_node_temp_terms_t &tef_terms) const
{
  if (type == eModelLocalVariable || type == eModFileLocalVariable)
    datatree.local_variables_table[symb_id]->compile(CompileCode, instruction_number, lhs_rhs, temporary_terms, map_idx, dynamic, steady_dynamic, tef_terms);
  else
    {
      int tsid = datatree.symbol_table.getTypeSpecificID(symb_id);
      if (type == eExogenousDet)
        tsid += datatree.symbol_table.exo_nbr();
      if (!lhs_rhs)
        {
          if (dynamic)
            {
              if (steady_dynamic)
                {
                  FLDVS_ fldvs(type, tsid);
                  fldvs.write(CompileCode, instruction_number);
                }
              else
                {
                  if (type == eParameter)
                    {
                      FLDV_ fldv(type, tsid);
                      fldv.write(CompileCode, instruction_number);
                    }
                  else
                    {
                      FLDV_ fldv(type, tsid, lag);
                      fldv.write(CompileCode, instruction_number);
                    }
                }
            }
          else
            {
              FLDSV_ fldsv(type, tsid);
              fldsv.write(CompileCode, instruction_number);
            }
        }
      else
        {
          if (dynamic)
            {
              if (steady_dynamic)
                {
                  cerr << "Impossible case: steady_state in rhs of equation" << endl;
                  exit(EXIT_FAILURE);
                }
              else
                {
                  if (type == eParameter)
                    {
                      FSTPV_ fstpv(type, tsid);
                      fstpv.write(CompileCode, instruction_number);
                    }
                  else
                    {
                      FSTPV_ fstpv(type, tsid, lag);
                      fstpv.write(CompileCode, instruction_number);
                    }
                }
            }
          else
            {
              FSTPSV_ fstpsv(type, tsid);
              fstpsv.write(CompileCode, instruction_number);
            }
        }
    }
}
