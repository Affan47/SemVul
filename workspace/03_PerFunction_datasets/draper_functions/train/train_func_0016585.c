processCadFileData()
{
  UserInterface* gui = theControlCenter->getGui();

  strstream strm;
  strm << "Nof bodies found: " << modelStatistics->nofBodies << ends;
  gui->showMsg(strm.str());

  if ( !checkBodyElementLoops() ) {
    return false;
  }


  int index = 0;
  while (true) {
    Body* body = getBody(index++);
    if (body==NULL) break;
    body->updateBoundBox();
  }

  if ( !checkBodies() ) {
    return false;
  }


  modelInfo->hasGeometry = true;

  findBoundaries();
  initBoundaries();
  setBoundaryParentIdsAndTags();
  findBodyPairs();
  findContainedBodies();


  if ( !checkElementGroupData() ) {
    return false;
  }

  markActiveObjects();

  setBoundaryTags();

  updateModelStatistics();

  setFlagValue(GEOMETRY_TYPE, GEOMETRY_TYPE_CAD, true);


  setInitialMeshH();

  return true;
}
