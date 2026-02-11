ajGraphDataAdd(AjPGraph thys, AjPGraphdata graphdata)
{
    if(thys->numofgraphs)
    {
        ajDebug("ajGraphDataAdd multi \n");
    }

    if(thys->numofgraphs < thys->numofgraphsmax)
    {
        (thys->graphs)[thys->numofgraphs++] = graphdata;
        return ajTrue;
    }

    ajErr("Too many multiple graphs - expected %d graphs",
          thys->numofgraphsmax);

    return ajFalse;
}
