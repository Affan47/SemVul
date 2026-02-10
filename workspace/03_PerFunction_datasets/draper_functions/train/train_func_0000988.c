is_valid(void) const
{
  if (csetup_repp == 0 ||
      csetup_repp->is_enabled() != true ||
      csetup_repp->is_valid() != true ||
      chains_repp == 0 ||
      chains_repp->size() == 0 ||
      inputs_repp == 0 ||
      inputs_repp->size() == 0 ||
      outputs_repp == 0 ||
      outputs_repp->size() == 0) {

    return false;
  }

  return true;
}
