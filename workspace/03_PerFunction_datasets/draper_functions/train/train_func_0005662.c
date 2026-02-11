external_server_mech_step(void *conn_context __attribute__((unused)),
			  sasl_server_params_t *sparams,
			  const char *clientin,
			  unsigned clientinlen,
			  const char **serverout,
			  unsigned *serveroutlen,
			  sasl_out_params_t *oparams)
{
    int result;

    if (!sparams
	|| !sparams->utils
	|| !sparams->utils->conn
	|| !sparams->utils->getcallback
	|| !serverout
	|| !serveroutlen
	|| !oparams)
	return SASL_BADPARAM;

    if (!sparams->utils->conn->external.auth_id)
	return SASL_BADPROT;


    if (clientinlen > 16384) return SASL_BADPROT;

    if ((sparams->props.security_flags & SASL_SEC_NOANONYMOUS) &&
	(!strcmp(sparams->utils->conn->external.auth_id, "anonymous"))) {
	sasl_seterror(sparams->utils->conn,0,"anonymous login not allowed");
	return SASL_NOAUTHZ;
    }

    *serverout = NULL;
    *serveroutlen = 0;

    if (!clientin) {


	return SASL_CONTINUE;
    }

    if (clientinlen) {


	result = sparams->canon_user(sparams->utils->conn,
				     clientin, 0,
				     SASL_CU_AUTHZID, oparams);
	if(result != SASL_OK) return result;

	result = sparams->canon_user(sparams->utils->conn,
				     sparams->utils->conn->external.auth_id, 0,
				     SASL_CU_AUTHID | SASL_CU_EXTERNALLY_VERIFIED, oparams);
    } else {
	result = sparams->canon_user(sparams->utils->conn,
				     sparams->utils->conn->external.auth_id, 0,
				     SASL_CU_AUTHID | SASL_CU_EXTERNALLY_VERIFIED | SASL_CU_AUTHZID, oparams);
    }

    if (result != SASL_OK) return result;


    oparams->doneflag = 1;
    oparams->mech_ssf = 0;
    oparams->maxoutbuf = 0;
    oparams->encode_context = NULL;
    oparams->encode = NULL;
    oparams->decode_context = NULL;
    oparams->decode = NULL;
    oparams->param_version = 0;

    return SASL_OK;
}
