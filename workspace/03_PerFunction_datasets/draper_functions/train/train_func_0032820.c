iterate_subgs(gxlstate_t * stp, Agraph_t * g)
{
    Agraph_t *subg;

    for (subg = agfstsubg(g); subg; subg = agnxtsubg(subg)) {
	iterateHdr(stp, subg);
	iterateBody(stp, subg);
    }
}
