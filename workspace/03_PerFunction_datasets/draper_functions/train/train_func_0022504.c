purpose_smime(const X509 *x, int ca)
{
	if(xku_reject(x,XKU_SMIME)) return 0;
	if(ca) {
		int ca_ret;
		ca_ret = check_ca(x);
		if(!ca_ret) return 0;

		if(ca_ret != 5 || x->ex_nscert & NS_SMIME_CA) return ca_ret;
		else return 0;
	}
	if(x->ex_flags & EXFLAG_NSCERT) {
		if(x->ex_nscert & NS_SMIME) return 1;

		if(x->ex_nscert & NS_SSL_CLIENT) return 2;
		return 0;
	}
	return 1;
}
