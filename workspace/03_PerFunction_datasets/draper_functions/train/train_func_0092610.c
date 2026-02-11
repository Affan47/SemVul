parse_pmt_desc(unsigned char *desc, int dlen,
			   struct psi_program *program, int pid)
{
    int i,t,l;

    for (i = 0; i < dlen; i += desc[i+1] +2) {
	t = desc[i];
	l = desc[i+1];

	switch (t) {
	case 0x56:
	    if (!program->t_pid)
		program->t_pid = pid;
	    break;
	}
    }
}
