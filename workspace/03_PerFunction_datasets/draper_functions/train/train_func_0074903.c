process_pkcs7(cert_payload_t *payload, auth_cfg_t *auth)
{
	enumerator_t *enumerator;
	container_t *container;
	certificate_t *cert;
	pkcs7_t *pkcs7;

	container = payload->get_container(payload);
	if (!container)
	{
		return;
	}
	switch (container->get_type(container))
	{
		case CONTAINER_PKCS7_DATA:
		case CONTAINER_PKCS7_SIGNED_DATA:
		case CONTAINER_PKCS7_ENVELOPED_DATA:
			break;
		default:
			container->destroy(container);
			return;
	}

	pkcs7 = (pkcs7_t *)container;
	enumerator = pkcs7->create_cert_enumerator(pkcs7);
	while (enumerator->enumerate(enumerator, &cert))
	{
		if (cert->get_type(cert) == CERT_X509)
		{
			x509_t *x509 = (x509_t*)cert;

			if (x509->get_flags(x509) & X509_CA)
			{
				DBG1(DBG_IKE, "received issuer cert \"%Y\"",
					 cert->get_subject(cert));
				auth->add(auth, AUTH_HELPER_IM_CERT, cert->get_ref(cert));
			}
			else
			{
				DBG1(DBG_IKE, "received end entity cert \"%Y\"",
					 cert->get_subject(cert));
				auth->add(auth, AUTH_HELPER_SUBJECT_CERT, cert->get_ref(cert));
			}
		}
		else
		{
			DBG1(DBG_IKE, "received unsupported cert type %N",
				 certificate_type_names, cert->get_type(cert));
		}
	}
	enumerator->destroy(enumerator);

	container->destroy(container);
}
