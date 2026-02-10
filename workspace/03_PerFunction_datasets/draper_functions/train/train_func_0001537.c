echoMatterTextureSet(echoScene *scene, echoObject *obj, Nrrd *ntext) {

  if (scene && obj && ntext && echoObjectHasMatter[obj->type] &&
      3 == ntext->dim &&
      nrrdTypeUChar == ntext->type &&
      4 == ntext->axis[0].size) {
    obj->ntext = ntext;
    _echoSceneNrrdAdd(scene, ntext);
  }
}
