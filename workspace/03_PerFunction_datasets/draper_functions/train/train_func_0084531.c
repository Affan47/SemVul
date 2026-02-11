getNodeIdsReversed(int elem_index)
{

  meshElementCode elem_code = getElementCode(elem_index);
  int nof_nodes = MeshElementDesc[elem_code][DESC_NOF_NODES];
  int* reversed = (int*)MeshElementReversedNodeIndices[elem_code];

  int* node_ids = nodeIds[elem_index];
  int* node_ids_reversed = getElementNodesBuffer();

  for (int i = 0; i < nof_nodes; i++) {
    node_ids_reversed[i] = node_ids[reversed[i]];
  }

  return node_ids_reversed;
}
