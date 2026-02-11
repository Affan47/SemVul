PerlCallbackCanonUser(sasl_conn_t *conn, void *context, const char *user, unsigned ulen,
					unsigned flags, const char *user_realm, char *out_user, unsigned out_umax,
					unsigned *out_ulen)
{
	struct _perlcontext *cp = (struct _perlcontext *) context;
	int rc = SASL_OK;
	Size_t len;
	char *c = NULL;

	AV *args;

	_DEBUG("Enter CanonUser user(%s,%d) user_realm(%s) out_user(%s) out_umax(%d).",user,ulen,user_realm,out_user,out_umax);

	if (!(flags & SASL_CU_AUTHID) && !(flags & SASL_CU_AUTHZID))
		return SASL_BADPARAM;

	args = newAV();


	av_push(args, newSVpv(user,ulen));
	av_push(args, newSViv(out_umax));
	av_push(args, newSVpv(user_realm == NULL ? "" : user_realm,0));
	av_push(args, newSVpv(flags & SASL_CU_AUTHID ? "AUTHID" : "AUTHZID" ,0));


	rc = PerlCallbackSub(cp,&c,&len,args);


	av_clear(args);
	av_undef(args);

	*out_ulen = len > out_umax ? out_umax : len;
	strncpy(out_user,c,*out_ulen);

	if (c != NULL)
		free(c);

	return rc;
}
