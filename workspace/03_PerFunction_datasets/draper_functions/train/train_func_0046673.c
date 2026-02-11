put(unsigned int new_value)
{
  trace.raw(write_trace.get() | value.get());
  value.put(new_value);

  if(m_spbrg)
    m_spbrg->set_start_cycle();
}
