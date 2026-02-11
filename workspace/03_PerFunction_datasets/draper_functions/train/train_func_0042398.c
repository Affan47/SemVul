kt_destroy (void *opt, int argc, char **argv)
{
    krb5_error_code ret;
    krb5_keytab keytab;

    if((keytab = ktutil_open_keytab()) == NULL)
	return 1;

    ret = krb5_kt_destroy (context, keytab);
    if (ret) {
	krb5_warn (context, ret, "destroy keytab failed");
	return 1;
    }

    return 0;
}
