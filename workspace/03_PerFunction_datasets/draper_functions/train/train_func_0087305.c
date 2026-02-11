PQinitialize(void)
{
    int i;

    PQcount = 0;
    PQmin = 0;
    PQhashsize = 4 * sqrt_nsites;
    if (PQhash == NULL)
	PQhash = N_GNEW(PQhashsize, Halfedge);
    for (i = 0; i < PQhashsize; i += 1)
	PQhash[i].PQnext = (Halfedge *) NULL;
}
