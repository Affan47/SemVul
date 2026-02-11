do_uninit_equivs(FILE *outfile, int *did_one)
#endif
{
    extern int nequiv;
    struct Equivblock *eqv, *lasteqv = eqvclass + nequiv;
    int k, last_type = -1, t;

    for (eqv = eqvclass; eqv < lasteqv; eqv++)
	if (!eqv -> eqvinit && eqv -> eqvtop != eqv -> eqvbottom) {
	    if (!*did_one)
		nice_printf (outfile, "/* System generated locals */\n");
	    t = eqv->eqvtype;
	    if (last_type == t)
		nice_printf (outfile, ", ");
	    else {
		if (*did_one)
		    nice_printf (outfile, ";\n");
		nice_printf (outfile, "static %s ", c_type_decl(t, 0));
		k = typesize[t];
	    }
	    nice_printf(outfile, "%s", equiv_name((int)(eqv - eqvclass), CNULL));
	    nice_printf(outfile, "[%ld]",
		(eqv->eqvtop - eqv->eqvbottom + k - 1) / k);
	    last_type = t;
	    *did_one = 1;
	}
}
