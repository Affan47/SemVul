print_system_identity (const identity *ident, const DATASET *dset,
		       gretlopt opt, PRN *prn)
{
    int i;

    if (opt & OPT_H) {
	pprintf(prn, "Identity: %s = %s ",
		dset->varname[ident->depvar],
		dset->varname[ident->atoms[0].varnum]);
    } else {
	pprintf(prn, "identity %s = %s ",
		dset->varname[ident->depvar],
		dset->varname[ident->atoms[0].varnum]);
    }

    for (i=1; i<ident->n_atoms; i++) {
	pprintf(prn, "%c %s ", (ident->atoms[i].op == OP_PLUS)? '+' : '-',
		dset->varname[ident->atoms[i].varnum]);
    }

    pputc(prn, '\n');
}
