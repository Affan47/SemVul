_XNormals(Field f, xfieldT* xf,
	      enum xr required)
{
    char *s;
    dependencyT normal_dep;

    ENTRY(("_XNormals(0x%x, 0x%x, %d)", f, xf, required));

    normal_dep = dep_none;
    array(normals_array, NORMALS, required);
    if (xf->normals_array && DXGetComponentValue(f, "binormals")) {

	xf->normals_array = NULL;
	EXIT(("not surface normals"));
	return OK;
    }
    check(normals, "normals", TYPE_FLOAT, 3);
    if(normal_dep != dep_field) {
      s = DXGetString((dxString)DXGetAttribute((dxObject)xf->normals_array, DEP));
      if (strcmp(s,"positions")==0) normal_dep = dep_positions;
      else if (strcmp(s,"connections")==0) normal_dep = dep_connections;
      else if (strcmp(s,"polylines")==0) normal_dep = dep_polylines;
#if 0
      else if (strcmp(s,"faces")==0) normal_dep = dep_faces;
#endif
      else {
	DXSetError(ERROR_MISSING_DATA, "#10256","normals","dep");
	EXIT(("ERROR"));
	return ERROR;
      }
      if (normal_dep==dep_positions) {
	compare(normals, "normals", xf->npositions);
      } else if (normal_dep==dep_connections) {
	compare(normals, "normals", xf->nconnections);
      } else if (normal_dep==dep_polylines) {
	compare(normals, "normals", xf->npolylines);
      } else {
	DXSetError(ERROR_DATA_INVALID, "#10256","normals","dep");
	EXIT(("ERROR"));
	return ERROR;
      }
    }
    _dxf_setFlags(_dxf_attributeFlags(_dxf_xfieldAttributes(xf)),
		  CONTAINS_NORMALS);
    xf->normalsDep = normal_dep;
    CHECK_CONST_ARRAY(normals);

    EXIT(("OK"));
    return OK;
}
