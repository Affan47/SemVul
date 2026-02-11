parse_pkcs12 (gnutls_pkcs12_t p12,
	      const char *password,
	      gnutls_x509_privkey_t * key,
	      gnutls_x509_crt_t * cert)
{
  gnutls_pkcs12_bag_t bag = NULL;
  int index = 0;
  int ret;

  for (;;)
    {
      int elements_in_bag;
      int i;

      ret = gnutls_pkcs12_bag_init (&bag);
      if (ret < 0)
	{
	  bag = NULL;
	  goto done;
	}

      ret = gnutls_pkcs12_get_bag (p12, index, bag);
      if (ret == GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE)
	break;
      if (ret < 0)
	{
	  goto done;
	}

      ret = gnutls_pkcs12_bag_get_type (bag, 0);
      if (ret < 0)
	{
	  goto done;
	}

      if (ret == GNUTLS_BAG_ENCRYPTED)
	{
	  ret = gnutls_pkcs12_bag_decrypt (bag, password);
	  if (ret < 0)
	    {
	      goto done;
	    }
	}

      elements_in_bag = gnutls_pkcs12_bag_get_count (bag);
      if (elements_in_bag < 0)
	{
	  goto done;
	}

      for (i = 0; i < elements_in_bag; i++)
	{
	  int type;
	  gnutls_datum_t data;

	  type = gnutls_pkcs12_bag_get_type (bag, i);
	  if (type < 0)
	    {
	      goto done;
	    }

	  ret = gnutls_pkcs12_bag_get_data (bag, i, &data);
	  if (ret < 0)
	    {
	      goto done;
	    }

	  switch (type)
	    {
	    case GNUTLS_BAG_PKCS8_ENCRYPTED_KEY:
	    case GNUTLS_BAG_PKCS8_KEY:
	      ret = gnutls_x509_privkey_init (key);
	      if (ret < 0)
		{
		  goto done;
		}

	      ret = gnutls_x509_privkey_import_pkcs8
		(*key, &data, GNUTLS_X509_FMT_DER, password,
		 type == GNUTLS_BAG_PKCS8_KEY ? GNUTLS_PKCS_PLAIN : 0);
	      if (ret < 0)
		{
		  goto done;
		}
	      break;

	    case GNUTLS_BAG_CERTIFICATE:
	      ret = gnutls_x509_crt_init (cert);
	      if (ret < 0)
		{
		  goto done;
		}

	      ret =
		gnutls_x509_crt_import (*cert, &data, GNUTLS_X509_FMT_DER);
	      if (ret < 0)
		{
		  goto done;
		}
	      break;

	    case GNUTLS_BAG_ENCRYPTED:


	    case GNUTLS_BAG_EMPTY:
	    default:
	      break;
	    }
	}

      index++;
      gnutls_pkcs12_bag_deinit (bag);
    }

  ret = 0;

done:
  if (bag)
    gnutls_pkcs12_bag_deinit (bag);

  return ret;
}
