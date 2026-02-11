exit_handler()
{
  DBUG_ENTER("sp_rcontext::exit_handler");
  DBUG_ASSERT(m_ihsp);

  uint hindex= m_in_handler[m_ihsp-1].index;
  m_raised_conditions[hindex].clear();
  m_ihsp-= 1;

  DBUG_PRINT("info", ("m_ihsp: %d", m_ihsp));
  DBUG_VOID_RETURN;
}
