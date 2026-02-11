connectPortToNoiseSource(LADSPA_Handle Instance,
			 unsigned long Port,
			 LADSPA_Data * DataLocation) {
  switch (Port) {
  case NOISE_AMPLITUDE:
    ((NoiseSource *)Instance)->m_pfAmplitudeValue = DataLocation;
    break;
  case NOISE_OUTPUT:
    ((NoiseSource *)Instance)->m_pfOutputBuffer = DataLocation;
    break;
  }
}
