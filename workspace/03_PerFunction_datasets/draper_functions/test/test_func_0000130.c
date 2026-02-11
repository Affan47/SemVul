d2i_PROXYCERTINFO_v4(PROXYCERTINFO ** cert_info, unsigned char ** pp, long length) {
  M_ASN1_D2I_vars(cert_info, PROXYCERTINFO *, PROXYCERTINFO_new);
  M_ASN1_D2I_Init();
  M_ASN1_D2I_start_sequence();
  M_ASN1_D2I_get_EXP_opt(ret->path_length, d2i_ASN1_INTEGER, 1);
  M_ASN1_D2I_get_opt(ret->path_length, d2i_ASN1_INTEGER, V_ASN1_INTEGER);

  c.q=c.p;
  if (d2i_PROXYPOLICY(&(ret->proxypolicy),(unsigned char**)&c.p,c.slen) == NULL)
   {c.line=__LINE__; goto err; }
  c.slen-=(c.p-c.q);

  ret->version = 4;
  M_ASN1_D2I_Finish(cert_info, PROXYCERTINFO_free, ASN1_F_D2I_PROXYCERTINFO);
}
