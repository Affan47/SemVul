krb5_encode(void *app_data, const void *from, int length, int level, void **to,
            struct connectdata *conn UNUSED_PARAM)
{
  gss_ctx_id_t *context = app_data;
  gss_buffer_desc dec, enc;
  OM_uint32 maj, min;
  int state;
  int len;


  conn = NULL;


  dec.value = (void*)from;
  dec.length = length;
  maj = gss_seal(&min, *context,
                 level == PROT_PRIVATE,
                 GSS_C_QOP_DEFAULT,
                 &dec, &state, &enc);

  if(maj != GSS_S_COMPLETE)
    return -1;


  *to = malloc(enc.length);
  if(!*to)
    return -1;
  memcpy(*to, enc.value, enc.length);
  len = curlx_uztosi(enc.length);
  gss_release_buffer(&min, &enc);
  return len;
}
