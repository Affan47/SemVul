addMeshInputElement(int el_type,
                                      int ext_elem_id, int parent_tag, int ext_parent_tag,
                                      int* ext_node_ids)
{
  static Timer timer;

  if (nofMeshInputElements == 0)
    timer.start();

  UserInterface* gui = theControlCenter->getGui();


	if ( nofMeshInputElements >= nofAllocMeshInputElements ) {
    gui->errMsg(1, "Fatal Error: Mesh: nof temporary elements incorrect");
    removeMeshInputElements();
		return ECIF_MESH_ELEMENT_INDEX_ERROR;
	}


  meshElementCode el_code = model->convertElementType(el_type);
  int nof_nodes = MeshElementDesc[el_code][DESC_NOF_NODES];

  MeshInputElement& te = meshInputElements[nofMeshInputElements];

  bool is_bulk, is_bndr, is_edge;
  checkMeshElementType(el_type, is_bulk, is_bndr, is_edge);

  if ( is_bulk)
    te.type = 'U';
  else if ( is_bndr )
    te.type = 'B';
  else if ( is_edge )
    te.type = 'E';
  else
    te.type = 'V';

  te.elementCode = el_code;
  te.extElementId = ext_elem_id;
  te.elementId = NO_INDEX;
  te.parentTag = parent_tag;
  te.extParentTag = ext_parent_tag;
  te.extNodeIds = new int[nof_nodes];


  for (int i = 0; i < nof_nodes; i++) {
    te.extNodeIds[i] = ext_node_ids[i];
  }

  meshInputElementsExt2Int[ext_elem_id] = nofMeshInputElements;

  nofMeshInputElements++;

  if ( te.type == 'U' ) {
    nofMeshInputBulkElements++;
  } else if ( te.type == 'B' ) {
    nofMeshInputBoundaryElements++;
  } else if ( te.type == 'E' ) {
    nofMeshInputEdgeElements++;
  } else if ( te.type == 'V' ) {
    nofMeshInputVertexElements++;
  }


  gui->showProgressMsg(timer, 2000,
                       nofMeshInputElements,
                       nofAllocMeshInputElements,
                       "Reading ", " elements ");

	return ECIF_OK;
}
