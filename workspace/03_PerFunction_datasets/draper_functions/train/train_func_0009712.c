epoch_resolve (gnutls_session_t session,
               unsigned int epoch_rel, uint16_t * epoch_out)
{
  switch (epoch_rel)
    {
    case EPOCH_READ_CURRENT:
      *epoch_out = session->security_parameters.epoch_read;
      return 0;

    case EPOCH_WRITE_CURRENT:
      *epoch_out = session->security_parameters.epoch_write;
      return 0;

    case EPOCH_NEXT:
      *epoch_out = session->security_parameters.epoch_next;
      return 0;

    default:
      if (epoch_rel > 0xffffu)
        return gnutls_assert_val (GNUTLS_E_INVALID_REQUEST);

      *epoch_out = epoch_rel;
      return 0;
    }
}
