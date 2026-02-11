_XPolylines(Field f, xfieldT *xf, enum xr required)
{
    array(polylines_array, POLYLINES, required);
    check(polylines, "polylines", TYPE_INT, 0);

    xf->polylines = (int *)DXGetArrayData(xf->polylines_array);
    DXGetArrayInfo(xf->polylines_array,
		&xf->npolylines, NULL, NULL, NULL, NULL);


    array(edges_array, "edges", required);
    check(edges, "edges", TYPE_INT, 0);

    xf->edges = (int *)DXGetArrayData(xf->edges_array);
    DXGetArrayInfo(xf->edges_array,
		&xf->nedges, NULL, NULL, NULL, NULL);

    xf->connectionType = ct_polylines;
    xf->nconnections = xf->npolylines;

    if (DXGetComponentValue(f, "invalid polylines"))
    {
      if (NULL == (xf->invCntns = DXCreateInvalidComponentHandle((dxObject)f,
								 NULL, "polylines")))
	  return ERROR;
    }

    return OK;
}
