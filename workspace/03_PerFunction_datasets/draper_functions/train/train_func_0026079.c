push_hstack(uint h)
{
  DBUG_ENTER("sp_rcontext::push_hstack");
  DBUG_ASSERT(m_hsp < m_root_parsing_ctx->max_handler_index());

  m_hstack[m_hsp++]= h;

  DBUG_PRINT("info", ("m_hsp: %d", m_hsp));
  DBUG_VOID_RETURN;
}
