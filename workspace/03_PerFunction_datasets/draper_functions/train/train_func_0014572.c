pam_authc(nssov_info *ni,TFILE *fp,Operation *op)
{
	int32_t tmpint32;
	int rc;
	slap_callback cb = {0};
	char dnc[1024];
	char uidc[32];
	char svcc[256];
	char pwdc[256];
	struct berval sdn, dn;
	struct paminfo pi;


	READ_STRING(fp,uidc);
	pi.uid.bv_val = uidc;
	pi.uid.bv_len = tmpint32;
	READ_STRING(fp,dnc);
	pi.dn.bv_val = dnc;
	pi.dn.bv_len = tmpint32;
	READ_STRING(fp,svcc);
	pi.svc.bv_val = svcc;
	pi.svc.bv_len = tmpint32;
	READ_STRING(fp,pwdc);
	pi.pwd.bv_val = pwdc;
	pi.pwd.bv_len = tmpint32;

	Debug(LDAP_DEBUG_TRACE,"nssov_pam_authc(%s)\n",pi.uid.bv_val,0,0);

	rc = pam_do_bind(ni, fp, op, &pi);

finish:
	WRITE_INT32(fp,NSLCD_VERSION);
	WRITE_INT32(fp,NSLCD_ACTION_PAM_AUTHC);
	WRITE_INT32(fp,NSLCD_RESULT_BEGIN);
	WRITE_BERVAL(fp,&pi.uid);
	WRITE_BERVAL(fp,&pi.dn);
	WRITE_INT32(fp,rc);
	WRITE_INT32(fp,pi.authz);
	WRITE_BERVAL(fp,&pi.msg);
	return 0;
}
