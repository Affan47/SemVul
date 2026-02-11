read_boundary()
{
  UserInterface* gui = theControlCenter->getGui();

  int i;
  bool result_code = true;

  int boundary_tag, external_body1_tag, external_body2_tag;
  int nof_bndr_elements;

  readFileLine(infile, read_buffer);
  istrstream strmline(read_buffer);

  if ( !(strmline >> boundary_tag
                  >> external_body1_tag >> external_body2_tag
                  >> nof_bndr_elements) ) {
    gui->errMsg(1, "could not read boundary data in InputThetis::read_boundaries()");
    return false;
  }

  int body1_tag = model->getBodyTagExt2Int(external_body1_tag);
  int body2_tag = model->getBodyTagExt2Int(external_body2_tag);

  int body1_lr = 0;
  int body2_lr = 0;


  BodyElement* be;

  if ( model->getDimension() == ECIF_2D )
    be = model->getEdgeByTag(boundary_tag);
  else
    be = model->getFaceByTag(boundary_tag);

  if (be != NULL) {
    be->allocateMeshElements(nof_bndr_elements);
  } else {
    model->createBodyElement(boundary_tag, body1_tag, body1_lr, body2_tag, body2_lr, nof_bndr_elements);
  }

  return result_code;
}
