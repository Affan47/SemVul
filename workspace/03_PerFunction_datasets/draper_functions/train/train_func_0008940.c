put(unsigned int new_value)
{
  unsigned int old_value = value.get();

  put_value(new_value);

  Dprintf(("SSPCON new %x old %x\n", new_value, old_value));
  if ((new_value & SSPEN) && ! (old_value & SSPEN))
       m_sspmod->startSSP(new_value);
  else if (!(new_value & SSPEN) &&  (old_value & SSPEN))
       m_sspmod->stopSSP(old_value);
  else if (new_value != old_value )
      m_sspmod->changeSSP(new_value, old_value);
}
