addAllPendingMeshElements()
{
  MeshInfo* mi = (MeshInfo*)model->getMeshInfo();

  int element_count = 0;

  if ( getObjectType() != OT_EDGE ||
       meshData == NULL ||
       meshData->nofPendingMeshElements == 0
     ) {
    return 0;
  }

  MeshElementTable* source = model->getMeshBoundaryElementEdges();

  for ( int i = 0; i < meshData->nofPendingMeshElements; i++) {

    int* info = meshData->pendingMeshElementInfos[i];

    int elem_code = info[0];

    info++;

    int nof_nodes = MeshElementDesc[elem_code][DESC_NOF_NODES];

    short dir, start;

    for ( int j = 0; j < source->NofElements(); j++) {

      if ( source->isSameElement(j, dir, start, elem_code, nof_nodes, info) ) {

        addMeshElement(j, dir);

        mi->nofUsedElementTypes[elem_code]++;

        element_count++;

        if ( element_count == meshData->nofPendingMeshElements ) {
          break;
        }

      }
    }

    if ( element_count == meshData->nofPendingMeshElements ) {
          break;
    }
  }


  return element_count;
}
