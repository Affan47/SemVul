opt_mark(sp_head *sp, List<sp_instr> *leads)
{
  sp_instr *i;

  marked= 1;
  if ((i= sp->get_instr(m_cont_dest)))
  {
    m_cont_dest= i->opt_shortcut_jump(sp, this);
    m_cont_optdest= sp->get_instr(m_cont_dest);
  }
  sp->add_mark_lead(m_cont_dest, leads);
  return m_ip+1;
}
