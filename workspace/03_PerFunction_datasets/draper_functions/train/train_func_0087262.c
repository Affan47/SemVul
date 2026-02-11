createMeshElementEdges(MeshElementTable* source, MeshElementTable* target)
{
  int node_ids[27];


  for (int elem_id = 0; elem_id < source->NofElements(); elem_id++) {

    meshElementCode elem_code = source->getElementCode(elem_id);


    int nof_edges = MeshElementDesc[elem_code][DESC_NOF_EDGES];
    meshElementCode edge_code = (meshElementCode)MeshElementDesc[elem_code][DESC_EDGE_ELEM_CODE];


    const int* elem_nodes = source->getNodeIds(elem_id);


    for (int edge = 0; edge < nof_edges; edge++) {

      int edge_id = source->edgeIds[elem_id][edge];


      if ( target->getElementCode(edge_id) != MEC_000 ) {
        continue;
      }


      int nof_edge_nodes = MeshElementDesc[edge_code][DESC_NOF_NODES];
      int* elem_edge_node_ids = (int*)MeshElementEdgeNodes[elem_code][edge];

      for (int i = 0; i < nof_edge_nodes; i++) {
        node_ids[i] = elem_nodes[elem_edge_node_ids[i]];
      }

      target->createTableEntry(edge_id, edge_code, NULL, nof_edge_nodes, node_ids);

    }

  }
}
