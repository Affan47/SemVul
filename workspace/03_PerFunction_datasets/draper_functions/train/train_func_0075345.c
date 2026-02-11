get()
  {
    RegisterValue rv = m_cpu->registers[m_addr]->getRV();
    RegisterValue retRV = rv.init ? m_unknown : m_cpu->registers[rv.data]->getRV();
    rv.data = (rv.data-2) & 0xffff;
    m_cpu->registers[m_addr]->putRV(rv);
    return retRV;
  }
