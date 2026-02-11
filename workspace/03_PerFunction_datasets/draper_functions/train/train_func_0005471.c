addSynapse()
{
  Synapse *s = new Synapse(&m_synapseDict);
  CHECK_PTR_ENGAUGE(s);

  return s;
}
