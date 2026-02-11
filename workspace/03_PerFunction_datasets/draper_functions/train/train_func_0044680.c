Curl_input_digest(struct connectdata *conn,
                           bool proxy,
                           const char *header)

{
  struct SessionHandle *data = conn->data;


  struct digestdata *digest;

  if(proxy) {
    digest = &data->state.proxydigest;
  }
  else {
    digest = &data->state.digest;
  }

  if(!checkprefix("Digest", header))
    return CURLE_BAD_CONTENT_ENCODING;

  header += strlen("Digest");
  while(*header && ISSPACE(*header))
    header++;

  return Curl_sasl_decode_digest_http_message(header, digest);
}
