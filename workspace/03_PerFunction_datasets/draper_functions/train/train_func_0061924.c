name() const
  {
    std::ostringstream nm;
    nm << "k_proc_" << dtohex(m_dens);
    return nm.str();
  }
