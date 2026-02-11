set_uf_array_from_names (fnpkg *pkg, char **names,
				    int n, int priv)
{
    ufunc **uf = NULL;
    ufunc *fun;
    int i;


    for (i=0; i<n; i++) {
	if (get_uf_array_member(names[i], NULL) == NULL) {
	    fprintf(stderr, "%s: function not found!\n", names[i]);
	    return E_DATA;
	}
    }


    if (n > 0) {
	uf = malloc(n * sizeof *uf);
	if (uf == NULL) {
	    return E_ALLOC;
	}
    }


    for (i=0; i<n; i++) {
	fun = get_uf_array_member(names[i], NULL);
	fun->pkg = pkg;
	set_function_private(fun, priv);
	check_special_comments(fun);
	uf[i] = fun;
    }


    if (priv) {
	pkg->priv = uf;
	pkg->n_priv = n;
    } else {
	pkg->pub = uf;
	pkg->n_pub = n;
    }

    return 0;
}
