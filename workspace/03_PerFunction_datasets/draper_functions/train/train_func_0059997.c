get_inputscale (graph_t* g)
{
    double d;

    if (PSinputscale > 0) return PSinputscale;
    d = late_double(g, agfindgraphattr(g, "inputscale"), -1, 0);
    if (d == 0) return POINTS_PER_INCH;
    else return d;
}
