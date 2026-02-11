readAndDistributeTriMesh(
     const std::string& meshName,
     const std::string& meshFileName,
     int tag)
{
  TriMeshDataPair meshData = readTriMesh(meshFileName,tag);
  createTriMesh(meshName, meshData.first, meshData.second);
}
