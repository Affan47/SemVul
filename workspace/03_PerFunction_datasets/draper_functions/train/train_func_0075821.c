ReadRayFile(const char *filename)
{

  FILE *fp;
  if (!(fp = fopen(filename, "r"))) {
    RNFail("Unable to open file %s", filename);
    return 0;
  }


  char cmd[128];
  int triangle_count = 0;
  int command_number = 1;
  while (fscanf(fp, "%s", cmd) == 1) {
    if (!strcmp(cmd, "#vertex")) {

      double px, py, pz;
      double nx, ny, nz;
      double ts, tt;
      if (fscanf(fp, "%lf%lf%lf%lf%lf%lf%lf%lf", &px, &py, &pz, &nx, &ny, &nz, &ts, &tt) != 8) {
        RNFail("Unable to read vertex at command %d in file %s", command_number, filename);
        return 0;
      }


      R3Point point(px, py, pz);
      R3Vector normal(nx, ny, nz);
      if (normal.IsZero()) CreateVertex(point);
      else CreateVertex(point, normal);
    }
    else if (!strcmp(cmd, "#shape_triangle")) {

      int m;
      int i1, i2, i3;
      if (fscanf(fp, "%d%d%d%d", &m, &i1, &i2, &i3) != 4) {
        RNFail("Unable to read triangle at command %d in file %s", command_number, filename);
        return 0;
      }


      R3MeshVertex *v1 = vertices.Kth(i1);
      R3MeshVertex *v2 = vertices.Kth(i2);
      R3MeshVertex *v3 = vertices.Kth(i3);


      if ((v1 == v2) || (v2 == v3) || (v1 == v3)) continue;


      R3MeshFace *face = CreateFace(v1, v2, v3);
      if (!face) {


      }


      if (face) SetFaceMaterial(face, m);
      if (face) SetFaceSegment(face, m);


      triangle_count++;
    }


    command_number++;
  }


  fclose(fp);


  return triangle_count;
}
