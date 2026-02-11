dn_indicates_v3_cert(X509_NAME *name)
{
#ifdef DISABLE_V3_LINKPROTO_CLIENTSIDE
  (void)name;
  return 0;
#else
  X509_NAME_ENTRY *entry;
  int n_entries;
  ASN1_OBJECT *obj;
  ASN1_STRING *str;
  unsigned char *s;
  int len, r;

  n_entries = X509_NAME_entry_count(name);
  if (n_entries != 1)
    return 1;
  entry = X509_NAME_get_entry(name, 0);

  obj = X509_NAME_ENTRY_get_object(entry);
  if (OBJ_obj2nid(obj) != OBJ_txt2nid("commonName"))
    return 1;

  str = X509_NAME_ENTRY_get_data(entry);
  len = ASN1_STRING_to_UTF8(&s, str);
  if (len < 0)
    return 0;
  r = fast_memneq(s + len - 4, ".net", 4);
  OPENSSL_free(s);
  return r;
#endif
}
