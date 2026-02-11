put(RegisterValue &n_rv)
  {
    RegisterValue rv = m_cpu->registers[m_addr]->getRV();
    if (rv.init == 0)
      m_cpu->registers[rv.data]->putRV(n_rv);
    rv.data = (rv.data+2) & 0xffff;
    m_cpu->registers[m_addr]->putRV(rv);
  }
