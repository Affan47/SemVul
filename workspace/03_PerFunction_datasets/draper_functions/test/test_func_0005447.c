getverifymic(gss_ctx_id_t cctx, gss_ctx_id_t sctx, gss_OID mechoid)
{
    gss_buffer_desc input_token, output_token;
    OM_uint32 min_stat, maj_stat;
    gss_qop_t qop_state;

    input_token.value = "bar";
    input_token.length = 3;

    maj_stat = gss_get_mic(&min_stat, cctx, 0, &input_token,
			   &output_token);
    if (maj_stat != GSS_S_COMPLETE)
	errx(1, "gss_get_mic failed: %s",
	     gssapi_err(maj_stat, min_stat, mechoid));

    maj_stat = gss_verify_mic(&min_stat, sctx, &input_token,
			      &output_token, &qop_state);
    if (maj_stat != GSS_S_COMPLETE)
	errx(1, "gss_verify_mic failed: %s",
	     gssapi_err(maj_stat, min_stat, mechoid));

    gss_release_buffer(&min_stat, &output_token);
}
