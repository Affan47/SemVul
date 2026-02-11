initialise_sine_wavetable(void)
{
  if (g_pfSineTable == NULL) {
    unsigned long lTableSize = (1 << SINE_TABLE_BITS);
    double dShift = (double(M_PI) * 2) / lTableSize;
    g_pfSineTable = new SAMPLE_SPECS::sample_t[lTableSize];
    if (g_pfSineTable != NULL)
      for (unsigned long lIndex = 0; lIndex < lTableSize; lIndex++)
	g_pfSineTable[lIndex] = SAMPLE_SPECS::sample_t(sin(dShift * lIndex));
  }
  if (g_fPhaseStepBase == 0) {
    g_fPhaseStepBase = (SAMPLE_SPECS::sample_t)pow(2, sizeof(unsigned long) * 8);
  }
}
