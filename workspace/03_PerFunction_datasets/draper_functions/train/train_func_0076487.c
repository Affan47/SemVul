addAllPendingVertices(int layer)
{
  if (!checkLayerIndex(layer)) return 0;

  int nof_vertex_tags = pendingVertexTags[layer]->size();

  if ( nof_vertex_tags == 0 )
    return 0;


  int* vertex_groups = new int[1 + nof_vertex_tags];
  int* vertex_ids = new int[1 + nof_vertex_tags];

  int nof_vertex_ids = 0;

  int i;

  for (i = 0; i < nof_vertex_tags; i++) {


    int v_group = (*pendingVertexGroups[layer])[i];
    int v_tag = (*pendingVertexTags[layer])[i];


    BodyElement* v = model->getVertexByTag(v_tag);

    if (v != NULL) {
      vertex_groups[nof_vertex_ids] = v_group;
      vertex_ids[nof_vertex_ids] = v->Id();
      nof_vertex_ids++;
    }
  }

  int nof_elements = 0;

  int groupd_id = vertex_groups[0];

  for (i = 1; i < nof_vertex_ids; i++) {

    int v1 = vertex_ids[i-1];
    int v2 = vertex_ids[i];


    if ( groupd_id == vertex_groups[i] ) {

      BodyElement* be = new BodyElement2D(v1, v2);
      addElement(layer, be);
      model->addBodyElement(be, false);
      nof_elements++;
    }

    groupd_id = vertex_groups[i];
  }

  pendingVertexGroups[layer]->clear();
  pendingVertexTags[layer]->clear();

  return nof_elements;
}
