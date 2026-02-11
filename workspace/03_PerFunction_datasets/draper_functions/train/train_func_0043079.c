parse_sdt_desc(unsigned char *desc, int dlen,
			   struct psi_program *pr)
{
    int i,t,l;
    char *name,*net;

    for (i = 0; i < dlen; i += desc[i+1] +2) {
	t = desc[i];
	l = desc[i+1];

	switch (t) {
	case 0x48:
	    pr->type = desc[i+2];
	    pr->updated = 1;
	    net = desc + i+3;
	    name = net + net[0] + 1;
	    mpeg_parse_psi_string(net+1,  net[0],  pr->net,  sizeof(pr->net));
	    mpeg_parse_psi_string(name+1, name[0], pr->name, sizeof(pr->name));
	    break;
	}
    }
}
