calc_phase (OPLL_SLOT * slot, e_int32 lfo)
{
  if (slot->patch->PM)
    slot->phase += (slot->dphase * lfo) >> PM_AMP_BITS;
  else
    slot->phase += slot->dphase;

  slot->phase &= (DP_WIDTH - 1);

  slot->pgout = HIGHBITS (slot->phase, DP_BASE_BITS);
}
