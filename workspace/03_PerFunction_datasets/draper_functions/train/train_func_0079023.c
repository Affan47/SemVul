get_poa_info(_CORBA_Unbounded_Sequence_Octet& key,
	     _CORBA_Unbounded_Sequence_String& poas_out,
	     int& transient_out,
	     _CORBA_Unbounded_Sequence_Octet& id_out)
{
  const char* k = (const char*) key.NP_data();
  int len = key.length();
  const char* kend = k + len;

  poas_out.length(1);
  poas_out[0] = CORBA::string_dup("root");

  if( *k != TRANSIENT_SUFFIX_SEP && *k != POA_NAME_SEP )  return 0;

  while( k < kend && *k == POA_NAME_SEP ) {

    k++;
    const char* name = k;

    while( k < kend && *k && *k != POA_NAME_SEP && *k != TRANSIENT_SUFFIX_SEP )
      k++;

    if( k == kend )  return 0;

    char* nm = new char[k - name + 1];
    memcpy(nm, name, k - name);
    nm[k - name] = '\0';
    poas_out.length(poas_out.length() + 1);
    poas_out[poas_out.length() - 1] = nm;
  }

  if( k == kend )  return 0;

  transient_out = 0;
  if( *k == TRANSIENT_SUFFIX_SEP ) {
    transient_out = 1;
    k += TRANSIENT_SUFFIX_SIZE + 1;
  }
  if( k >= kend || *k )  return 0;
  k++;

  id_out.length(kend - k);
  memcpy(id_out.NP_data(), k, kend - k);

  return 1;
}
