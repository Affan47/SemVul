gnutls_pkcs12_bag_set_data (gnutls_pkcs12_bag_t bag,
                            gnutls_pkcs12_bag_type_t type,
                            const gnutls_datum_t * data)
{
  int ret;
  if (bag == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  if (bag->bag_elements == MAX_BAG_ELEMENTS - 1)
    {
      gnutls_assert ();

      return GNUTLS_E_MEMORY_ERROR;
    }

  if (bag->bag_elements == 1)
    {


      if (bag->element[0].type == GNUTLS_BAG_PKCS8_KEY ||
          bag->element[0].type == GNUTLS_BAG_PKCS8_ENCRYPTED_KEY ||
          bag->element[0].type == GNUTLS_BAG_ENCRYPTED)
        {
          gnutls_assert ();
          return GNUTLS_E_INVALID_REQUEST;
        }
    }

  ret =
    _gnutls_set_datum (&bag->element[bag->bag_elements].data,
                       data->data, data->size);

  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  bag->element[bag->bag_elements].type = type;

  bag->bag_elements++;

  return bag->bag_elements - 1;
}
