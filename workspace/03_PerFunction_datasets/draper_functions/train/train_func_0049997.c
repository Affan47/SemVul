writeOutput(ostream &output, bool block) const
{
  if (!block)
    return;

  unsigned int nb_blocks = getNbBlocks();
  for (int b = 0; b < (int) nb_blocks; b++)
    {
      BlockSimulationType simulation_type = getBlockSimulationType(b);
      unsigned int block_size = getBlockSize(b);
      ostringstream tmp_s, tmp_s_eq;
      tmp_s.str("");
      tmp_s_eq.str("");
      for (unsigned int i = 0; i < block_size; i++)
        {
          tmp_s << " " << getBlockVariableID(b, i)+1;
          tmp_s_eq << " " << getBlockEquationID(b, i)+1;
        }
      output << "block_structure_stat.block(" << b+1 << ").Simulation_Type = " << simulation_type << ";\n";
      output << "block_structure_stat.block(" << b+1 << ").endo_nbr = " << block_size << ";\n";
      output << "block_structure_stat.block(" << b+1 << ").mfs = " << getBlockMfs(block) << ";\n";
      output << "block_structure_stat.block(" << b+1 << ").equation = [" << tmp_s_eq.str() << "];\n";
      output << "block_structure_stat.block(" << b+1 << ").variable = [" << tmp_s.str() << "];\n";
    }
  output << "M_.block_structure_stat.block = block_structure_stat.block;\n";
  string cst_s;
  int nb_endo = symbol_table.endo_nbr();
  output << "M_.block_structure_stat.variable_reordered = [";
  for (int i = 0; i < nb_endo; i++)
    output << " " << variable_reordered[i]+1;
  output << "];\n";
  output << "M_.block_structure_stat.equation_reordered = [";
  for (int i = 0; i < nb_endo; i++)
    output << " " << equation_reordered[i]+1;
  output << "];\n";

  map<pair<int, int>,  int>  row_incidence;
  for (first_derivatives_t::const_iterator it = first_derivatives.begin();
       it != first_derivatives.end(); it++)
    {
      int deriv_id = it->first.second;
      if (getTypeByDerivID(deriv_id) == eEndogenous)
        {
          int eq = it->first.first;
          int symb = getSymbIDByDerivID(deriv_id);
          int var = symbol_table.getTypeSpecificID(symb);

          row_incidence[make_pair(eq, var)] = 1;
        }
    }
  output << "M_.block_structure_stat.incidence.sparse_IM = [";
  for (map<pair< int, int >,  int>::const_iterator it = row_incidence.begin(); it != row_incidence.end(); it++)
    {
      output << it->first.first+1 << " " << it->first.second+1 << ";\n";
    }
  output << "];\n";
}
