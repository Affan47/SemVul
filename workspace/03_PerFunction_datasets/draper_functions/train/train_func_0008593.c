findSelectedMeshElement(Renderer* renderer,
                                     Point3& ray_start, Point3& ray_dir,
                                     Point3& isec_point,
                                     int& bndr_id,
                                     int& body1_id, int& layer1_id,
                                     int& body2_id, int& layer2_id)
{
  bndr_id = id;
  body1_id = NO_INDEX;
  body2_id = NO_INDEX;
  layer1_id = NO_INDEX;
  layer2_id = NO_INDEX;

  if ( meshData == NULL || meshData->nofMeshElements == 0 ||
       drawMode == DM_HIDDEN
     ) {
    return NO_INDEX;
  }

  int bd1_id = modelData->parent1Id;
  int bd2_id = modelData->parent2Id;

  Body* bd1 = model->getBodyById(bd1_id);
  Body* bd2 = model->getBodyById(bd2_id);

  int lr1_id = NO_INDEX;
  int lr2_id = NO_INDEX;

  if ( bd1 != NULL ) {
    lr1_id = bd1->getLayerId(modelData->parent1Layer);
  }

  if ( bd2 != NULL ) {
    lr2_id = bd2->getLayerId(modelData->parent2Layer);
  }


  if ( (bd1 == NULL || bd1->getDrawMode() == DM_HIDDEN) &&
       (bd2 == NULL || bd2->getDrawMode() == DM_HIDDEN)
     ) {
    return NO_INDEX;
  }


  if ( ECIF_3D == model->getDimension() &&
       (bd1_id != bd2_id) &&
       (bd1 != NULL && bd1->getDrawMode() != DM_HIDDEN) &&
       (bd2 != NULL && bd2->getDrawMode() != DM_HIDDEN)
     ) {
    return NO_INDEX;
  }

  short direction;

  if ( bd1->getDrawMode() == DM_HIDDEN ) {
    body1_id = bd2_id;
    body2_id = bd1_id;
    layer1_id = lr2_id;
    layer2_id = lr1_id;
    direction = -1;

  } else {
    body1_id = bd1_id;
    body2_id = bd2_id;
    layer1_id = lr1_id;
    layer2_id = lr2_id;
    direction = 1;
  }


  if ( isBemBoundary() ) {
    direction = 0;
  }

  flagName select_mode = model->getSelectionMode();

  MeshElementTable* elements = model->getMeshBoundaryElements();
  MeshElementTable* parents = model->getMeshBulkElements();

  double min_distance = 1.0e100;
  int isec_elem_index = NO_INDEX;

  for (int i = 0; i < meshData->nofMeshElements; i++) {

    int elem_index = meshData->meshElementIds[i];

    int nof_isections = elements->calcLineIntersections(elem_index, direction,
                                                        ray_start, ray_dir,
                                                        &isec_point);
#if 0
    if ( nof_isections > 0 ) {
      return elem_index;
    }
#endif

    if ( nof_isections == 0 ) {
      continue;
    }

    double distance = ray_start[2] - isec_point[2];

    distance = (distance < 0 ) ? -distance : distance;

    if ( distance < min_distance ) {
      min_distance = distance;
      isec_elem_index = elem_index;
    }

  }


  return isec_elem_index;
}
