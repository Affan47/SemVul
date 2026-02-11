ToWebOOGL(QvState *state)
{
    QvElement *elt = NULL;
    QvCoordinate3 *qv_coord = NULL;
    QvMaterial *qv_material = NULL;
    QvMaterialBinding *qv_materialb = NULL;
    float *coords;

    int   count, numcoords;
    long numverts;

    elt = state->getTopElement(QvState::Coordinate3Index);
    if (elt) { qv_coord = (QvCoordinate3 *)elt->data;}
    elt = state->getTopElement(QvState::MaterialIndex);
    if (elt) { qv_material = (QvMaterial *)elt->data;}
    elt = state->getTopElement(QvState::MaterialBindingIndex);
    if (elt) { qv_materialb = (QvMaterialBinding *)elt->data; }


    if (qv_coord) {
      numcoords = qv_coord->point.num;
      coords = qv_coord->point.values;
    } else { numcoords = 0; coords = NULL; }

    if (qv_material) {
    }

    if (startIndex.value > numcoords) {
      OOGLout("# Bad Values");
      return;
    }

    if (numPoints.value == (-1)) {
      numverts = numcoords - startIndex.value;
    } else if ((numPoints.value - startIndex.value) > numcoords) {
      OOGLout("# Bad Values");
      return;
    } else {
      numverts = numPoints.value - startIndex.value;
    }

    ANNOUNCE(QvPointSet);

    OOGLout("# PointSet");
    if (coords == NULL) {
      OOGLout("# Bad Values");
      return;
    }
    OOGLout("{ = VECT");
    sprintf(out, "%d %d %d\n", numverts, numverts, numverts);
    OOGLout(out);


    OOGLoutindent();
    for (count = 0; count < numverts; count++) {
      OOGLoutraw("1 ");
    }
    OOGLoutraw("\n");


    OOGLoutindent();
    for (count = 0; count < numverts; count++) {
      OOGLoutraw("1 ");
    }
    OOGLoutraw("\n");

    for (count = 0; count < numverts; count++)
    {
      float x = coords[(count+startIndex.value)*3],
      y = coords[(count+startIndex.value)*3+1],
      z = coords[(count+startIndex.value)*3+2];

      sprintf(out, "%f %f %f", x, y, z);
      OOGLout(out);
    }
    OOGLout("");

    for (count = 0; count < numverts; count++) {
      OOGLgetcolor(qv_material, qv_materialb, count);
      OOGLout(colstr);
    }
    OOGLout("}");

}
