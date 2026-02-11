nssCertificateArray_Destroy (
  NSSCertificate **certs
)
{
    if (certs) {
	NSSCertificate **certp;
	for (certp = certs; *certp; certp++) {
	    if ((*certp)->decoding) {
		CERTCertificate *cc = STAN_GetCERTCertificate(*certp);
		if (cc) {
		    CERT_DestroyCertificate(cc);
		}
		continue;
	    }
	    nssCertificate_Destroy(*certp);
	}
	nss_ZFreeIf(certs);
    }
}
