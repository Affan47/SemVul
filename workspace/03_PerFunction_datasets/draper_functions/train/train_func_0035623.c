icode_to_fcode(root, lenp)
	struct block *root;
	u_int *lenp;
{
	u_int n;
	struct bpf_insn *fp;


	while (1) {
	    unMarkAll();
	    n = *lenp = count_stmts(root);

	    fp = (struct bpf_insn *)malloc(sizeof(*fp) * n);
	    if (fp == NULL)
		    bpf_error("malloc");
	    memset((char *)fp, 0, sizeof(*fp) * n);
	    fstart = fp;
	    ftail = fp + n;

	    unMarkAll();
	    if (convert_code_r(root))
		break;
	    free(fp);
	}

	return fp;
}
