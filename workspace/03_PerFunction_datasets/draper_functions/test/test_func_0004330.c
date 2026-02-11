_gnutls_tls_aid_to_sign (const sign_algorithm_st * aid)
{
  gnutls_sign_algorithm_t ret = GNUTLS_SIGN_UNKNOWN;

  if (memcmp(aid, &unknown_tls_aid, sizeof(*aid))==0)
    return ret;

  GNUTLS_SIGN_LOOP (if (p->aid.hash_algorithm == aid->hash_algorithm
                        && p->aid.sign_algorithm == aid->sign_algorithm)
                    {
                      ret = p->id; break;
                    }
  );


  return ret;
}
