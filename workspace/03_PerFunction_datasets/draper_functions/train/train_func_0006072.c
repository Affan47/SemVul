do_cont_backpatch()
{
  uint dest= instructions();
  uint lev= m_cont_level--;
  sp_instr_opt_meta *i;

  while ((i= m_cont_backpatch.head()) && i->m_cont_dest == lev)
  {
    i->m_cont_dest= dest;
    (void)m_cont_backpatch.pop();
  }
}
