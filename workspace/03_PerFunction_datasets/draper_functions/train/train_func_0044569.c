response1(struct sasl_state* ss,
		     const str* response, str* challenge)
{
  char binresp[16];
  const str binrespstr = { binresp, 16, 0 };
  unsigned i;
  unsigned j;
  if (response->len == 0) return SASL_RESP_BAD;
  if ((i = str_findfirst(response, ' ')) == (unsigned)-1
      || response->len - i != 33)
    return SASL_RESP_BAD;
  response->s[i] = 0;
  for (j = 0; j < 32; j += 2)
    binresp[j/2] = hex2bin[(unsigned char)response->s[i+j]] << 4
      | hex2bin[(unsigned char)response->s[i+j+1]];
  return sasl_authenticate_cram(ss, response->s, "CRAM-MD5",
				&ss->init, &binrespstr);
  (void)challenge;
}
