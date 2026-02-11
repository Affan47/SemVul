zxid_extract_private_key(char* buf, char* name)
{
  char* p;
  char* e;
  int typ;
  EVP_PKEY* pk = 0;
  OpenSSL_add_all_algorithms();

  if (p = strstr(buf, PEM_RSA_PRIV_KEY_START)) {
    typ = EVP_PKEY_RSA;
    e = PEM_RSA_PRIV_KEY_END;
    p += sizeof(PEM_RSA_PRIV_KEY_START) - 1;
  } else if (p = strstr(buf, PEM_DSA_PRIV_KEY_START)) {
    typ = EVP_PKEY_DSA;
    e = PEM_DSA_PRIV_KEY_END;
    p += sizeof(PEM_DSA_PRIV_KEY_START) - 1;
  } else if (p = strstr(buf, PEM_PRIV_KEY_START)) {
    typ = EVP_PKEY_RSA;
    e = PEM_PRIV_KEY_END;
    p += sizeof(PEM_PRIV_KEY_START) - 1;
  } else {
    ERR("No private key found in file(%s). Looking for separator (%s) or (%s).\npem data(%s)", name, PEM_RSA_PRIV_KEY_START, PEM_DSA_PRIV_KEY_START, buf);
    return 0;
  }
  if (*p == 0xd) ++p;
  if (*p != 0xa) {
    ERR("Bad privkey missing newline ch(0x%x) at %ld (%.*s) of buf(%s)", *p, (long)(p-buf), 5, p-2, buf);
    return 0;
  }
  ++p;

  e = strstr(buf, e);
  if (!e) {
    ERR("End marker not found, typ=%d", typ);
    return 0;
  }

  p = unbase64_raw(p, e, buf, zx_std_index_64);
  if (!d2i_PrivateKey(typ, &pk, (const unsigned char**)&buf, p-buf) || !pk) {
    zx_report_openssl_err("extract_private_key");
    ERR("DER decoding of private key failed.\n%d", 0);
    return 0;
  }
  zx_report_openssl_err("extract_private_key2");
  return pk;
}
