rank(graph_t * g, int balance, int maxiter)
{
    char *s;
    int search_size;

    if ((s = agget(g, "searchsize")))
	search_size = atoi(s);
    else
	search_size = SEARCHSIZE;

    return rank2 (g, balance, maxiter, search_size);
}
