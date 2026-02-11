connectPortToSineOscillator(LADSPA_Handle Instance,
                            unsigned long Port,
                            LADSPA_Data * DataLocation) {
  switch (Port) {
  case OSC_FREQUENCY:
    ((SineOscillator *)Instance)->m_pfFrequency = DataLocation;
    break;
  case OSC_AMPLITUDE:
    ((SineOscillator *)Instance)->m_pfAmplitude = DataLocation;
    break;
  case OSC_OUTPUT:
    ((SineOscillator *)Instance)->m_pfOutput = DataLocation;
    break;
  }
}
