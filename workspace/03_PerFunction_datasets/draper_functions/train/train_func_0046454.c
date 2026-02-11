_dxf_XPositions(Field f, struct xfield *xf, enum xr required, enum xd xd)
{
    array(positions_array, POSITIONS, required);
    get(positions, xd);
    return OK;
}
