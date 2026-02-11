PQdump(void)
{
    int i;
    Halfedge *p;

    for (i = 0; i < PQhashsize; i += 1) {
	printf("[%d]\n", i);
	p = PQhash[i].PQnext;
	while (p != NULL) {
	    PQdumphe(p);
	    p = p->PQnext;
	}
    }

}
