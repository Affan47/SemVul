get_peers_certificate (std::vector < gnutls_datum_t >
				       &out_certs) const
  {
    const gnutls_datum_t *certs;
    unsigned int certs_size;

      certs = gnutls_certificate_get_peers (s, &certs_size);

    if (certs == NULL)
      return false;

    for (unsigned int i = 0; i < certs_size; i++)
      out_certs.push_back (certs[i]);

      return true;
  }
