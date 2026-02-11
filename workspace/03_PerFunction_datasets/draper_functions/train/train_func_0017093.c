agnxtsubg(Agraph_t * subg)
{
    Agraph_t *g;

    g = agparent(subg);
    return g? (Agraph_t *) dtnext(g->g_dict, subg) : 0;
}
