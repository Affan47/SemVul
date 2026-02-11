writeCovarAndCorrShocks(ostream &output) const
{
  covar_and_corr_shocks_t::const_iterator it;

  for (it = covar_shocks.begin(); it != covar_shocks.end(); it++)
    writeCovarOrCorrShock(output, it, false);

  for (it = corr_shocks.begin(); it != corr_shocks.end(); it++)
    writeCovarOrCorrShock(output, it, true);
}
