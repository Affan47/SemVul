reallocateMeshBoundaryElements(int new_size)
{


  meshData->boundaryElements->resize(new_size, NULL);


  int old_size = meshData->boundaryElements->NofElements();
  int copy_size = (new_size >= old_size)? old_size: new_size;
  int i;


  int* tmp1 = new int[new_size];


  for (i = 0; i < copy_size; i++) {
    tmp1[i] = meshData->boundaryElementBoundaryIds[i];
  }


  for(i = old_size; i < new_size; i++) {
    tmp1[i] = NO_INDEX;
  }


  delete[] meshData->boundaryElementBoundaryIds;
  meshData->boundaryElementBoundaryIds = tmp1;
  meshInfo->nofBoundaryElements = new_size;
}
