or_handshake_state_record_var_cell(or_handshake_state_t *state,
                                   const var_cell_t *cell,
                                   int incoming)
{
  crypto_digest_t *d, **dptr;
  char buf[VAR_CELL_HEADER_SIZE];
  if (incoming) {
    if (!state->digest_received_data)
      return;
  } else {
    if (!state->digest_sent_data)
      return;
  }
  dptr = incoming ? &state->digest_received : &state->digest_sent;
  if (! *dptr)
    *dptr = crypto_digest256_new(DIGEST_SHA256);

  d = *dptr;

  var_cell_pack_header(cell, buf);
  crypto_digest_add_bytes(d, buf, sizeof(buf));
  crypto_digest_add_bytes(d, (const char *)cell->payload, cell->payload_len);

  memset(buf, 0, sizeof(buf));
}
