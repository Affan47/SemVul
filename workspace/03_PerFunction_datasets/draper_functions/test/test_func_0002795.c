epoch_get_slot (gnutls_session_t session, uint16_t epoch)
{
  uint16_t epoch_index = epoch - session->security_parameters.epoch_min;

  if (epoch_index >= MAX_EPOCH_INDEX)
    {
      gnutls_assert ();
      return NULL;
    }


  return &session->record_parameters[epoch_index];
}
