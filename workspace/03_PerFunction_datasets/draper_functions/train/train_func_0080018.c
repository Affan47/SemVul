krb5_digest_request(krb5_context context,
		    krb5_digest digest,
		    krb5_realm realm,
		    krb5_ccache ccache)
{
    DigestReqInner ireq;
    DigestRepInner irep;
    krb5_error_code ret;

    memset(&ireq, 0, sizeof(ireq));
    memset(&irep, 0, sizeof(irep));

    ireq.element = choice_DigestReqInner_digestRequest;
    ireq.u.digestRequest = digest->request;

    if (digest->request.type == NULL) {
	if (digest->init.type == NULL) {
	    krb5_set_error_message(context, EINVAL,
				   N_("Type missing from req", ""));
	    return EINVAL;
	}
	ireq.u.digestRequest.type = digest->init.type;
    }

    if (ireq.u.digestRequest.digest == NULL) {
	static char md5[] = "md5";
	ireq.u.digestRequest.digest = md5;
    }

    ret = digest_request(context, realm, ccache,
			 KRB5_KU_DIGEST_ENCRYPT, &ireq, &irep);
    if (ret)
	return ret;

    if (irep.element == choice_DigestRepInner_error) {
	ret = irep.u.error.code;
	krb5_set_error_message(context, ret,
			       N_("Digest response error: %s", ""),
			       irep.u.error.reason);
	goto out;
    }

    if (irep.element != choice_DigestRepInner_response) {
	krb5_set_error_message(context, EINVAL,
			       N_("digest reply not an DigestResponse", ""));
	ret = EINVAL;
	goto out;
    }

    ret = copy_DigestResponse(&irep.u.response, &digest->response);
    if (ret) {
	krb5_set_error_message(context, ret,
			       N_("Failed to copy initReply,", ""));
	goto out;
    }

 out:
    free_DigestRepInner(&irep);

    return ret;
}
