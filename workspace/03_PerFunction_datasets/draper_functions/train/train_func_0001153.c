gar_nod_parse_nod3(struct gar_subfile *sub)
{
	int i, rc;
	off_t o;
	int x,y,p;
	struct nod_bond nb;
	if (!sub->net || !sub->net->nod) {
		return -1;
	}

	if (!sub->net->nod->nod3_offset || !sub->net->nod->nod3_length) {
		log(1, "NOD: No boundary nodes defined\n");
		return 0;
	}
	log(11, "nod3recsize=%d nodbond=%d\n",  sub->net->nod->nod3_recsize,
			 sizeof(struct nod_bond));
	o = sub->net->nod->nodoff + sub->net->nod->nod3_offset;
	if (glseek(sub->gimg, o, SEEK_SET) != o) {
		log(1, "NOD: Error can not seek to %ld\n", o);
		return 0;
	}
	log(11, "Boundary nodes %d\n", sub->net->nod->nod3_length/sub->net->nod->nod3_recsize);
	for (i=0; i < sub->net->nod->nod3_length/sub->net->nod->nod3_recsize; i++) {
		rc = gread(sub->gimg, &nb, sizeof(struct nod_bond));
		if (rc != sizeof(struct nod_bond)) {
			log(1, "NOD: Can not read node\n");
			return 0;
		}
		x = get_u24(&nb.east);
		x = SIGN3B(x);
		y = get_u24(&nb.north);
		y = SIGN3B(y);
		p = get_u24(&nb.offset);
		log(11, "%d %f %f %x\n", i,  GARDEG(x), GARDEG(y), p);
	}
	return 0;
}
