drawMeshBulkElement(int elem_type, const int* elem_nodes,
                              objectDrawingState dstate,
                              const Point3* node_data)
{
  if (dstate == DS_SELECTED) {
    glPolygonMode(GL_FRONT, GL_FILL);
  }

  drawMeshElement(elem_type, elem_nodes, NULL, node_data);

  if (dstate == DS_SELECTED) {
    glPolygonMode(GL_FRONT, GL_LINE);
  }

}
