amdmsInitStripeSetup(amdmsSTRIPE_SETUP *setup)
{
  int             iStripe;

  if (setup == NULL) {
    return amdmsFAILURE;
  }
  setup->nHStripes = 0;
  setup->nVStripes = 0;
  for (iStripe = 0; iStripe < amdmsMAX_STRIPES; iStripe++) {
    setup->hStripes[iStripe].pos = 0;
    setup->hStripes[iStripe].size = 0;
    setup->hStripes[iStripe].flags = amdmsUSE_NOTHING;
    setup->vStripes[iStripe].pos = 0;
    setup->vStripes[iStripe].size = 0;
    setup->vStripes[iStripe].flags = amdmsUSE_NOTHING;
  }
  return amdmsSUCCESS;
}
