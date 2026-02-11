_get_pk_dsa_raw (gnutls_openpgp_crt_t crt, gnutls_openpgp_keyid_t keyid,
                 gnutls_datum_t * p, gnutls_datum_t * q,
                 gnutls_datum_t * g, gnutls_datum_t * y)
{
  int pk_algorithm, ret, i;
  cdk_packet_t pkt;
  uint32_t kid32[2];
  bigint_t params[MAX_PUBLIC_PARAMS_SIZE];
  int params_size = MAX_PUBLIC_PARAMS_SIZE;

  if (crt == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  KEYID_IMPORT (kid32, keyid);

  pkt = _gnutls_openpgp_find_key (crt->knode, kid32, 0);
  if (pkt == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_OPENPGP_GETKEY_FAILED;
    }

  pk_algorithm = _gnutls_openpgp_get_algo (pkt->pkt.public_key->pubkey_algo);

  if (pk_algorithm != GNUTLS_PK_DSA)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  ret = _gnutls_openpgp_crt_get_mpis (crt, kid32, params, &params_size);
  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }


  ret = _gnutls_mpi_dprint (params[0], p);
  if (ret < 0)
    {
      gnutls_assert ();
      goto cleanup;
    }


  ret = _gnutls_mpi_dprint (params[1], q);
  if (ret < 0)
    {
      gnutls_assert ();
      _gnutls_free_datum (p);
      goto cleanup;
    }


  ret = _gnutls_mpi_dprint (params[2], g);
  if (ret < 0)
    {
      gnutls_assert ();
      _gnutls_free_datum (p);
      _gnutls_free_datum (q);
      goto cleanup;
    }


  ret = _gnutls_mpi_dprint (params[3], y);
  if (ret < 0)
    {
      gnutls_assert ();
      _gnutls_free_datum (p);
      _gnutls_free_datum (g);
      _gnutls_free_datum (q);
      goto cleanup;
    }

  ret = 0;

cleanup:
  for (i = 0; i < params_size; i++)
    {
      _gnutls_mpi_release (&params[i]);
    }
  return ret;
}
