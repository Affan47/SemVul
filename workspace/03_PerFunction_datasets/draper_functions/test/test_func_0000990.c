readElementGroup(int& body_counter, int& bndr_counter,
                             int& element_counter, int& max_ext_elem_id,
                             bool count_only)
{
  int element_group_counter = 0;

  while ( element_group_counter < nofElementGroups &&
          !infile.eof()
          ) {

    element_group_counter++;


    FidapElementGroupInfo gi;


    if ( !readElementGroupInfo(gi) )
      return ECIF_ERROR;

    if ( !setElementType(gi) )
      return ECIF_ERROR;

    gi.parentTag = NO_INDEX;


    model->checkMeshElementType(gi.elementType,
                                gi.isBulk,
                                gi.isBoundary,
                                gi.isEdge);


    if (gi.isBulk) {

      nofBulkElements += gi.nofElements;


      Body* body = findExistingBody(&gi);


      if (body == NULL) {

        int int_id = ++body_counter;
        int ext_id = gi.id;

        if ( modelDimension == ECIF_2D ) {
          body = new Body2D(MESH_BODY, int_id, ext_id, 0, NULL);

        } else if ( modelDimension == ECIF_3D ) {
          body = new Body3D(MESH_BODY, int_id, ext_id, 0, NULL);
        }

        if (body != NULL) {
          model->addBody(body);
          body->setName(gi.entityName);
        }
      }


      if ( body != NULL ) {
        gi.parentTag = body->Tag();
      }


    } else if (gi.isBoundary) {

      nofBoundaryElements += gi.nofElements;


      BodyElement* be = findExistingBoundary(&gi);


      if ( be == NULL ) {

        int int_id = ++bndr_counter;


        if ( modelDimension == ECIF_2D ) {
          be = new BodyElement2D(int_id, NO_INDEX, NO_INDEX, gi.nofElements);

        } else if ( modelDimension == ECIF_3D ) {
          be = new BodyElement3D(int_id, NO_INDEX, NO_INDEX, gi.nofElements);
        }

        if (be != NULL) {
          model->addBodyElement(be);
          be->setName(gi.entityName);
        }
      }


      if ( be != NULL ) {
        gi.parentTag = be->Tag();
      }

    }


    if ( ECIF_OK != readElements(gi, element_counter, max_ext_elem_id, count_only) ) {
      return ECIF_ERROR;
    }
  }

  return ECIF_OK;
}
