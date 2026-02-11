selectMeshBoundaryElementsAll()
{
  BodyElement* be = model->getBoundaryById(modelInfo->selectedBodyElementId);

  if (be == NULL)
    return;

  int nof_elements = be->getNofMeshElements();

  for (int i = 0; i < nof_elements; i++) {

    int index = be->getMeshElementId(i);
    selectMeshBoundaryElement(index);
  }

  model->refreshRenderer();
}
