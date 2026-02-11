gsskrb5_get_creds(
        OM_uint32 * minor_status,
	krb5_context context,
	krb5_ccache ccache,
	gsskrb5_ctx ctx,
	gss_const_name_t target_name,
	int use_dns,
	OM_uint32 time_req,
	OM_uint32 * time_rec)
{
    OM_uint32 ret;
    krb5_error_code kret;
    krb5_creds this_cred;
    OM_uint32 lifetime_rec;

    if (ctx->target) {
	krb5_free_principal(context, ctx->target);
	ctx->target = NULL;
    }
    if (ctx->kcred) {
	krb5_free_creds(context, ctx->kcred);
	ctx->kcred = NULL;
    }

    ret = _gsskrb5_canon_name(minor_status, context, use_dns,
			      ctx->source, target_name, &ctx->target);
    if (ret)
	return ret;

    memset(&this_cred, 0, sizeof(this_cred));
    this_cred.client = ctx->source;
    this_cred.server = ctx->target;

    if (time_req && time_req != GSS_C_INDEFINITE) {
	krb5_timestamp ts;

	krb5_timeofday (context, &ts);
	this_cred.times.endtime = ts + time_req;
    } else {
	this_cred.times.endtime   = 0;
    }

    this_cred.session.keytype = KEYTYPE_NULL;

    kret = krb5_get_credentials(context,
				0,
				ccache,
				&this_cred,
				&ctx->kcred);
    if (kret) {
	*minor_status = kret;
	return GSS_S_FAILURE;
    }

    ctx->lifetime = ctx->kcred->times.endtime;

    ret = _gsskrb5_lifetime_left(minor_status, context,
				 ctx->lifetime, &lifetime_rec);
    if (ret) return ret;

    if (lifetime_rec == 0) {
	*minor_status = 0;
	return GSS_S_CONTEXT_EXPIRED;
    }

    if (time_rec) *time_rec = lifetime_rec;

    return GSS_S_COMPLETE;
}
