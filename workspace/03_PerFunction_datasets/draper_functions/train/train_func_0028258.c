writeOutput(ostream &output, const string &basename) const
{
  output << "%" << endl
         << "% SHOCKS instructions" << endl
         << "%" << endl;


  output << "make_ex_;" << endl;

  writeDetShocks(output);
  writeVarAndStdShocks(output);
  writeCovarAndCorrShocks(output);
  if (covar_shocks.size()+corr_shocks.size() > 0)
    output << "M_.sigma_e_is_diagonal = 0;" << endl;
  else
    output << "M_.sigma_e_is_diagonal = 1;" << endl;
}
