setMeshBgMeshFileIndices(int nof_files, int* bg_mesh_file_indices)
{
  int i;

  delete[] modelInfo->meshBgMeshFileIndices;

  modelInfo->nofBgMeshFiles = nof_files;
  modelInfo->meshBgMeshFileIndices = NULL;

  if ( nof_files > 0 ) {


    modelInfo->meshBgMeshFileIndices = new int[nof_files];

    for (i = 0; i < nof_files; i++) {
      modelInfo->meshBgMeshFileIndices[i] = bg_mesh_file_indices[i];
    }
  }
}
