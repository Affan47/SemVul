drawMeshQuadriElement(int elem_type, const int* node_ids,
                                    const Point3*  nodes, const Point3*  nodeNormals,
                                    short direction, bool selected)
{

  if (selected) {

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, selectColor);
  }

  glBegin(GL_POLYGON);

    for (int i = 0; i < 4; i++) {
      if ( nodeNormals != NULL ) {
        glNormal3dv(nodeNormals[i]);
      }
      glVertex3dv(nodes[node_ids[i]]);
    }

  glEnd();


  if (selected) {

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, currentColor);
  }


#if 0
  if ( nodeNormals != NULL ) {
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, meshColor);
    drawVector((double*)nodes[node_ids[0]], (double*)nodeNormals[0], 0.05 * modelLength[0]);
    drawVector((double*)nodes[node_ids[1]], (double*)nodeNormals[1], 0.05 * modelLength[0]);
    drawVector((double*)nodes[node_ids[2]], (double*)nodeNormals[2], 0.05 * modelLength[0]);
    drawVector((double*)nodes[node_ids[3]], (double*)nodeNormals[3], 0.05 * modelLength[0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, currentColor);
  }
#endif

}
