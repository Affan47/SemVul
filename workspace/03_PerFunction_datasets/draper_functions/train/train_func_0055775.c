print_package_code (const fnpkg *pkg, PRN *prn)
{
    int i;

    if (pkg->priv != NULL) {
	for (i=0; i<pkg->n_priv; i++) {
	    gretl_function_print_code(pkg->priv[i], prn);
	    pputc(prn, '\n');
	}
    }

    if (pkg->pub != NULL) {
	for (i=0; i<pkg->n_pub; i++) {
	    gretl_function_print_code(pkg->pub[i], prn);
	    pputc(prn, '\n');
	}
    }
}
