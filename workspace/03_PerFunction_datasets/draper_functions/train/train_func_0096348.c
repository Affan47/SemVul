isInnerBoundary()
{
  if ( ( (getObjectType() == OT_EDGE && model->getDimension() == ECIF_2D) ||
         (getObjectType() == OT_FACE && model->getDimension() == ECIF_3D)
       ) &&
       modelData != NULL &&
       modelData->parent1Id != NO_INDEX &&
       modelData->parent2Id != NO_INDEX &&
       !isIntraLayerBoundary()
     ) {
    return true;

  } else {
    return false;
  }
}
