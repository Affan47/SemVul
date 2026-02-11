connectPortToAutotalent(LADSPA_Handle Instance,
		       unsigned long Port,
		       LADSPA_Data * DataLocation) {

  Autotalent * psAutotalent;

  psAutotalent = (Autotalent *)Instance;
  switch (Port) {
  case AT_TUNE:
    psAutotalent->m_pfTune = DataLocation;
    break;
  case AT_FIXED:
    psAutotalent->m_pfFixed = DataLocation;
    break;
  case AT_PULL:
    psAutotalent->m_pfPull = DataLocation;
    break;
  case AT_A:
    psAutotalent->m_pfA = DataLocation;
    break;
  case AT_Bb:
    psAutotalent->m_pfBb = DataLocation;
    break;
  case AT_B:
    psAutotalent->m_pfB = DataLocation;
    break;
  case AT_C:
    psAutotalent->m_pfC = DataLocation;
    break;
  case AT_Db:
    psAutotalent->m_pfDb = DataLocation;
    break;
  case AT_D:
    psAutotalent->m_pfD = DataLocation;
    break;
  case AT_Eb:
    psAutotalent->m_pfEb = DataLocation;
    break;
  case AT_E:
    psAutotalent->m_pfE = DataLocation;
    break;
  case AT_F:
    psAutotalent->m_pfF = DataLocation;
    break;
  case AT_Gb:
    psAutotalent->m_pfGb = DataLocation;
    break;
  case AT_G:
    psAutotalent->m_pfG = DataLocation;
    break;
  case AT_Ab:
    psAutotalent->m_pfAb = DataLocation;
    break;
  case AT_AMOUNT:
    psAutotalent->m_pfAmount = DataLocation;
    break;
  case AT_SMOOTH:
    psAutotalent->m_pfSmooth = DataLocation;
    break;
  case AT_SHIFT:
    psAutotalent->m_pfShift = DataLocation;
    break;
  case AT_SCWARP:
    psAutotalent->m_pfScwarp = DataLocation;
    break;
  case AT_LFOAMP:
    psAutotalent->m_pfLfoamp = DataLocation;
    break;
  case AT_LFORATE:
    psAutotalent->m_pfLforate = DataLocation;
    break;
  case AT_LFOSHAPE:
    psAutotalent->m_pfLfoshape = DataLocation;
    break;
  case AT_LFOSYMM:
    psAutotalent->m_pfLfosymm = DataLocation;
    break;
  case AT_LFOQUANT:
    psAutotalent->m_pfLfoquant = DataLocation;
    break;
  case AT_FCORR:
    psAutotalent->m_pfFcorr = DataLocation;
    break;
  case AT_FWARP:
    psAutotalent->m_pfFwarp = DataLocation;
    break;
  case AT_MIX:
    psAutotalent->m_pfMix = DataLocation;
    break;
  case AT_PITCH:
    psAutotalent->m_pfPitch = DataLocation;
    break;
  case AT_CONF:
    psAutotalent->m_pfConf = DataLocation;
    break;
  case AT_INPUT1:
    psAutotalent->m_pfInputBuffer1 = DataLocation;
    break;
  case AT_OUTPUT1:
    psAutotalent->m_pfOutputBuffer1 = DataLocation;
    break;
  case AT_LATENCY:
    psAutotalent->m_pfLatency = DataLocation;
    *(psAutotalent->m_pfLatency) = psAutotalent->cbsize - 1;
    break;
  }
}
