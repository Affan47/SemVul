check_policy_constraints(x509_t *issuer, u_int pathlen,
									 auth_cfg_t *auth)
{
	certificate_t *subject;
	bool valid = TRUE;

	subject = auth->get(auth, AUTH_RULE_SUBJECT_CERT);
	if (subject)
	{
		if (subject->get_type(subject) == CERT_X509)
		{
			x509_cert_policy_t *policy;
			enumerator_t *enumerator;
			linked_list_t *chain;
			certificate_t *cert;
			auth_rule_t rule;
			x509_t *x509;
			int len = 0;
			u_int expl, inh;
			char *oid;


			chain = linked_list_create();
			enumerator = auth->create_enumerator(auth);
			while (enumerator->enumerate(enumerator, &rule, &cert))
			{
				if (rule == AUTH_RULE_IM_CERT &&
					cert->get_type(cert) == CERT_X509)
				{
					chain->insert_last(chain, cert);
				}
			}
			enumerator->destroy(enumerator);
			chain->insert_last(chain, issuer);


			enumerator = chain->create_enumerator(chain);
			while (enumerator->enumerate(enumerator, &x509))
			{
				expl = x509->get_constraint(x509, X509_REQUIRE_EXPLICIT_POLICY);
				if (expl != X509_NO_CONSTRAINT)
				{
					if (!has_policy_chain(chain, (x509_t*)subject, len - expl))
					{
						valid = FALSE;
						break;
					}
				}
				len++;
			}
			enumerator->destroy(enumerator);


			len = 0;
			chain->insert_first(chain, subject);
			enumerator = chain->create_enumerator(chain);
			while (enumerator->enumerate(enumerator, &x509))
			{
				inh = x509->get_constraint(x509, X509_INHIBIT_POLICY_MAPPING);
				if (inh != X509_NO_CONSTRAINT)
				{
					if (!has_no_policy_mapping(chain, len - inh))
					{
						valid = FALSE;
						break;
					}
				}
				inh = x509->get_constraint(x509, X509_INHIBIT_ANY_POLICY);
				if (inh != X509_NO_CONSTRAINT)
				{
					if (!has_no_any_policy(chain, len - inh))
					{
						valid = FALSE;
						break;
					}
				}
				len++;
			}
			enumerator->destroy(enumerator);

			if (valid)
			{
				x509 = (x509_t*)subject;

				enumerator = x509->create_cert_policy_enumerator(x509);
				while (enumerator->enumerate(enumerator, &policy))
				{
					oid = asn1_oid_to_string(policy->oid);
					if (oid)
					{
						if (is_policy_valid(chain, policy->oid))
						{
							auth->add(auth, AUTH_RULE_CERT_POLICY, oid);
						}
						else
						{
							DBG1(DBG_CFG, "certificate policy %s for '%Y' "
								 "not allowed by trustchain, ignored",
								 oid, subject->get_subject(subject));
							free(oid);
						}
					}
				}
				enumerator->destroy(enumerator);
			}
			chain->destroy(chain);
		}
	}
	return valid;
}
