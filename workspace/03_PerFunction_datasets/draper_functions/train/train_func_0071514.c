ossl_x509_set_version(VALUE self, VALUE version)
{
    X509 *x509;
    long ver;

    if ((ver = NUM2LONG(version)) < 0) {
	ossl_raise(eX509CertError, "version must be >= 0!");
    }
    GetX509(self, x509);
    if (!X509_set_version(x509, ver)) {
	ossl_raise(eX509CertError, NULL);
    }

    return version;
}
