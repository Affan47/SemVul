hc128_extract(hc128_state *state, uint8_t *stream)
{
  uint16_t i = state->i;
  state->i = (i + 1u) & 1023u;

  register uint32_t ret = (i < 512)
    ? round_expression(state->p, state->q, g1, i      )
    : round_expression(state->q, state->p, g2, m512(i));

  unpack_littleendian(ret, stream);
}
