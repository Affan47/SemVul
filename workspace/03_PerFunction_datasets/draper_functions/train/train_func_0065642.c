xlhorder(XLabels_t * xlp)
{
    double maxx = xlp->params->bb.UR.x, maxy = xlp->params->bb.UR.y;
    return floorLog2(maxx > maxy ? maxx : maxy) + 1;
}
