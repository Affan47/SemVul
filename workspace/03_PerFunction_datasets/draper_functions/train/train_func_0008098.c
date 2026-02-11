resetMeshEdgesSelected()
{
#if 0
  if (meshData->bulkEdges != NULL)
    meshData->bulkEdges->resetSelected();
#endif

  if (meshData->boundaryEdges!= NULL)
    meshData->boundaryEdges->resetSelected();

  if (meshData->boundaryVertices!= NULL)
    meshData->boundaryVertices->resetSelected();

}
