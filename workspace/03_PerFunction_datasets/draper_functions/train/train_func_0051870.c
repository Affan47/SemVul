updateGeometryType()
{

  switch (modelSourceType) {
  case ECIF_CAD_OR_MESH_FILE:
    geometryType = GEOM_CAD_OR_MESH;
    break;
  case ECIF_CAD_FILE:
    geometryType = GEOM_CAD;
    break;
  case ECIF_MESH_FILE:
    geometryType = GEOM_MESH;
    break;
  case ECIF_CAD_AND_MESH_FILE:
    geometryType = GEOM_CAD_AND_MESH;
    break;
  }

  return geometryType;
}
