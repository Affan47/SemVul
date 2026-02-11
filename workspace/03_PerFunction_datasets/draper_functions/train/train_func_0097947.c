calcInitialMeshH()
{
  double initial_mesh_h = MAX_RANGE;

  if (modelInfo->dimMin > 0 && modelInfo->dimMin < initial_mesh_h)
    initial_mesh_h = MESH_H_INIT_FACTOR * modelInfo->dimMin;

  if (modelInfo->minEdgeSize > 0 && modelInfo->minEdgeSize < initial_mesh_h)
    initial_mesh_h = modelInfo->minEdgeSize;

  return initial_mesh_h;

}
