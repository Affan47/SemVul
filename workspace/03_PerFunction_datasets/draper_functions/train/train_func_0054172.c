cryptopan_anon(struct cryptopan *cp, u_int32_t orig_addr, u_int32_t *new_addr)
{
  u_int8_t rin_output[16];
  u_int8_t rin_input[16];
  u_int8_t *m_pad;
  u_int32_t result, first4bytes_pad, first4bytes_input;
  int i, pos;

  result = 0;
  m_pad = cp->m_pad;

  bcopy(m_pad, rin_input, 16);

  first4bytes_pad = (((u_int32_t) m_pad[0]) << 24) +
                    (((u_int32_t) m_pad[1]) << 16) +
                    (((u_int32_t) m_pad[2]) << 8) +
                    (u_int32_t) m_pad[3];


  for (pos = 0; pos <= 31 ; pos++) {


    if (pos == 0)
      first4bytes_input =  first4bytes_pad;
    else
      first4bytes_input = ((orig_addr >> (32-pos)) << (32-pos)) |
        ((first4bytes_pad<<pos) >> pos);

    rin_input[0] = (u_int8_t) (first4bytes_input >> 24);
    rin_input[1] = (u_int8_t) ((first4bytes_input << 8) >> 24);
    rin_input[2] = (u_int8_t) ((first4bytes_input << 16) >> 24);
    rin_input[3] = (u_int8_t) ((first4bytes_input << 24) >> 24);


    i = 16;
#ifdef HAVE_OPENSSL
    if (!(EVP_EncryptUpdate(cp->cipher_ctx, rin_output, &i, rin_input, i))) {
      cryptopan_free(cp);
      return -1;
    }
#endif

    result |=  (rin_output[0] >> 7) << (31-pos);

  }


  *new_addr = result ^ orig_addr;

  return 0;

}
