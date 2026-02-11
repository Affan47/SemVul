_pkcs12_bag_free_data (gnutls_pkcs12_bag_t bag)
{
  int i;

  for (i = 0; i < bag->bag_elements; i++)
    {
      _gnutls_free_datum (&bag->element[i].data);
      _gnutls_free_datum (&bag->element[i].local_key_id);
      gnutls_free (bag->element[i].friendly_name);
      bag->element[i].friendly_name = NULL;
      bag->element[i].type = 0;
    }

}
