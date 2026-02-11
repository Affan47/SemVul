addElementComponent(ecif_Element_X& tx, ecif_geometryType gtype)
{

  int nof_components = tx.nof_components;
  tx.nof_components++;


  ecif_ElementComponent_X** components = new ecif_ElementComponent_X*[tx.nof_components];

  for (int i = 0; i < nof_components; i++) {
    components[i] = tx.components[i];
  }


  delete[] tx.components;
  tx.components = components;


  ecif_ElementComponent_X* txc = new ecif_ElementComponent_X;
  init_trx_data(*txc);
  txc->gmtr_type = gtype;

  tx.components[tx.nof_components - 1] = txc;


  if ( tx.tplg_type == ECIF_VERTEX) {
    txc->geometry.vertex = new ecif_VertexGeometry_X;
    init_trx_data(*txc->geometry.vertex);

  } else if ( tx.tplg_type == ECIF_EDGE) {
    txc->geometry.edge = new ecif_EdgeGeometry_X;
    init_trx_data(*txc->geometry.edge);

  } else if ( tx.tplg_type == ECIF_FACE ) {
    txc->geometry.face = new ecif_FaceGeometry_X;
    init_trx_data(*txc->geometry.face);
  }

  return true;
}
