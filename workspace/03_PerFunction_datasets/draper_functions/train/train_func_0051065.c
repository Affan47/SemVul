addIntersection(const SbVec3f & objectspacepoint_in, SbBool frontpick)
{
  if (PRIVATE(this)->isFlagSet(SoRayPickActionP::CULL_BACKFACES) && !frontpick)
    return NULL;

  SbVec3d objectspacepoint;
  objectspacepoint.setValue(objectspacepoint_in);
  SbVec3d worldpoint;
  PRIVATE(this)->obj2world.multVecMatrix(objectspacepoint, worldpoint);
  double dist = PRIVATE(this)->isFlagSet(SoRayPickActionP::PUSH_PICK_TO_FRONT) ?
    0.0 : PRIVATE(this)->nearplane.getDistance(worldpoint);

  if (!PRIVATE(this)->isFlagSet(SoRayPickActionP::PICK_ALL) && PRIVATE(this)->pickedpointlist.getLength()) {

    if (dist >= PRIVATE(this)->ppdistance[0]) return NULL;

    PRIVATE(this)->pickedpointlist.truncate(0);
    PRIVATE(this)->ppdistance.truncate(0);
  }


  SoPickedPoint * pp = new SoPickedPoint(this->getCurPath(),
                                         this->state, objectspacepoint_in);
  PRIVATE(this)->pickedpointlist.append(pp);
  PRIVATE(this)->ppdistance.append(dist);
  PRIVATE(this)->clearFlag(SoRayPickActionP::PPLIST_IS_SORTED);
  return pp;
}
