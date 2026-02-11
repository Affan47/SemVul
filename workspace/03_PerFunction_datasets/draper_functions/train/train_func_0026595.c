_gnutls_pkcs11_privkey_sign_hash (gnutls_pkcs11_privkey_t key,
                                  const gnutls_datum_t * hash,
                                  gnutls_datum_t * signature)
{
  ck_rv_t rv;
  int ret;
  struct ck_mechanism mech;
  unsigned long siglen;
  struct ck_function_list *module;
  ck_session_handle_t pks;
  ck_object_handle_t obj;

  FIND_OBJECT (module, pks, obj, key);

  mech.mechanism =
    key->pk_algorithm == GNUTLS_PK_DSA ? CKM_DSA : CKM_RSA_PKCS;
  mech.parameter = NULL;
  mech.parameter_len = 0;


  rv = pkcs11_sign_init (module, pks, &mech, obj);
  if (rv != CKR_OK)
    {
      gnutls_assert ();
      ret = pkcs11_rv_to_err (rv);
      goto cleanup;
    }


  rv = pkcs11_sign (module, pks, hash->data, hash->size, NULL, &siglen);
  if (rv != CKR_OK)
    {
      gnutls_assert ();
      ret = pkcs11_rv_to_err (rv);
      goto cleanup;
    }

  signature->data = gnutls_malloc (siglen);
  signature->size = siglen;

  rv = pkcs11_sign (module, pks, hash->data, hash->size, signature->data, &siglen);
  if (rv != CKR_OK)
    {
      gnutls_free (signature->data);
      gnutls_assert ();
      ret = pkcs11_rv_to_err (rv);
      goto cleanup;
    }

  signature->size = siglen;

  ret = 0;

cleanup:
  pkcs11_close_session (module, pks);

  return ret;
}
