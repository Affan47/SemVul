compute_extent_for_list_of_distributions(int n,
					 DistributionSpecStructLabeled* distrList,
					 ergo_real threshold,
					 ergo_real maxLimitingFactor,
					 ergo_real maxabsDmatelement)
{
  ergo_real requested_erfcinv_accuracy = 0.001;
  for(int i = 0; i < n; i++)
    {
      ergo_real erfc_inverse_value = erfc_inverse(threshold / (distrList[i].limitingFactor * maxLimitingFactor * maxabsDmatelement), requested_erfcinv_accuracy);
      distrList[i].distr.extent = erfc_inverse_value / std::sqrt(distrList[i].distr.exponent);
    }
}
