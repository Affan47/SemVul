opj_stream_set_write_function(opj_stream_t* p_stream, opj_stream_write_fn p_function)
{
  opj_stream_private_t* l_stream = (opj_stream_private_t*) p_stream;
  if
    ((!l_stream )|| (! (l_stream->m_status & opj_stream_e_output)))
  {
    return;
  }
  l_stream->m_write_fn = p_function;
}
