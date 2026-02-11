to_tk_WriteStats(Tcl_Interp* interp, const Model& model)
{
  const ModelStatistics* mstats = model.getModelStatistics();
  const ModelInfo* minfo = model.getModelInfo();
  const MeshInfo* mesh_info = model.getMeshInfo();

  writeVariable(interp, "Model", "nofBodies", mstats->nofBodies);
  writeVariable(interp, "Model", "nofElements", mstats->nofOuterBoundaries + mstats->nofInnerBoundaries);
  writeVariable(interp, "Model", "nofOuterBoundaries", mstats->nofOuterBoundaries);
  writeVariable(interp, "Model", "nofInnerBoundaries", mstats->nofInnerBoundaries);
  writeVariable(interp, "Model", "nofVertices", mstats->nofVertices);
  writeVariable(interp, "Model", "minEdgeSize", minfo->minEdgeSize);


  if (minfo->minX < minfo->maxX) {
    writeVariable(interp, "Model", "minX", minfo->minX);
    writeVariable(interp, "Model", "maxX", minfo->maxX);
    writeVariable(interp, "Model", "minY", minfo->minY);
    writeVariable(interp, "Model", "maxY", minfo->maxY);
    writeVariable(interp, "Model", "minZ", minfo->minZ);
    writeVariable(interp, "Model", "maxZ", minfo->maxZ);

  } else {
    writeVariable(interp, "Model", "minX", mesh_info->minX);
    writeVariable(interp, "Model", "maxX", mesh_info->maxX);
    writeVariable(interp, "Model", "minY", mesh_info->minY);
    writeVariable(interp, "Model", "maxY", mesh_info->maxY);
    writeVariable(interp, "Model", "minZ", mesh_info->minZ);
    writeVariable(interp, "Model", "maxZ", mesh_info->maxZ);
  }

  int nof_zv_elements = mesh_info->nofZeroVelocityElements;
  int nof_sp_elements = mesh_info->nofSplittedElements;

  writeVariable(interp, "Model", "nofMeshElements", mesh_info->nofBulkElements);
  writeVariable(interp, "Model", "nofMeshSplittedElements", nof_sp_elements);
  writeVariable(interp, "Model", "nofMeshZeroVelocityElements", nof_zv_elements);
  writeVariable(interp, "Model", "nofMeshBndrElements", mesh_info->nofBoundaryElements);
  writeVariable(interp, "Model", "nofMeshInnerBndrElements", mesh_info->nofInnerBndrElements);
  writeVariable(interp, "Model", "nofMeshOuterBndrElements", mesh_info->nofOuterBndrElements);
  writeVariable(interp, "Model", "nofMeshNodes", mesh_info->nofNodes);

  sendCommandToGui(interp, "Interface::applyStatsData");
}
