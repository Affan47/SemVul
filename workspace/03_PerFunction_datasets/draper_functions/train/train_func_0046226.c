_dxf_XPolylines(Field f, struct xfield *xf, enum xr required, enum xd xd)
{
    array(polylines_array, POLYLINES, required);
    check(polylines, "polylines", TYPE_INT, 0);
    get(polylines, xd);


    array(edges_array, "edges", required);
    check(edges, "edges", TYPE_INT, 0);
    get(edges, xd);

    xf->ct = ct_polylines;
    xf->nconnections = xf->npolylines;

    return OK;
}
