tenModelFromAxisLearnPossible(const NrrdAxisInfo *axinfo) {


  return (nrrdKind3DSymMatrix == axinfo->kind
          || nrrdKind3DMaskedSymMatrix == axinfo->kind
          || airStrlen(axinfo->label));
}
