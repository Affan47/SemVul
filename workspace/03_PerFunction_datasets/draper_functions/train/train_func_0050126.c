print()
{
  Processor *pCpu = GetActiveCPU(true);
  if(pCpu)
    cout << "Clock frequency: " << pCpu->get_frequency()/1e6 << " MHz.\n";
}
