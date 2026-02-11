opt_mark(sp_head *sp, List<sp_instr> *leads)
{
  m_dest= opt_shortcut_jump(sp, this);
  if (m_dest != m_ip+1)
    marked= 1;
  m_optdest= sp->get_instr(m_dest);
  return m_dest;
}
