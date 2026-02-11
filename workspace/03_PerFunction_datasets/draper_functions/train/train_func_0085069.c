makeDphaseDRTable (void)
{
  e_int32 DR, Rks, RM, RL;

#ifdef USE_SPEC_ENV_SPEED
  e_uint32 decaytable[16][4];

  for (RM = 0; RM < 16; RM++)
    for (RL = 0; RL < 4; RL++)
      if (RM == 0)
        decaytable[RM][RL] = 0;
      else
        decaytable[RM][RL] = (e_uint32) ((double) (1 << EG_DP_BITS) / (decaytime[RM][RL] * 3579545 / 72000));
#endif

  for (DR = 0; DR < 16; DR++)
    for (Rks = 0; Rks < 16; Rks++)
    {
      RM = DR + (Rks >> 2);
      RL = Rks & 3;
      if (RM > 15)
        RM = 15;
      switch (DR)
      {
      case 0:
        dphaseDRTable[DR][Rks] = 0;
        break;
      default:
#ifdef USE_SPEC_ENV_SPEED
        dphaseDRTable[DR][Rks] = rate_adjust (decaytable[RM][RL]);
#else
        dphaseDRTable[DR][Rks] = rate_adjust ((RL + 4) << (RM - 1));
#endif
        break;
      }
    }
}
