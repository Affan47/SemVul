GetFaceZoneMesh(
    vtkMultiBlockDataSet *faceZoneMesh,
    const vtkFoamIntVectorVector *facesPoints, vtkPoints *points)
{
  vtkFoamDict *faceZoneDictPtr = this->GatherBlocks("faceZones", false);

  if (faceZoneDictPtr == NULL)
    {

    return true;
    }

  vtkFoamDict &faceZoneDict = *faceZoneDictPtr;
  int nFaceZones = static_cast<int>(faceZoneDict.size());

  for (int i = 0; i < nFaceZones; i++)
    {

    vtkFoamDict &dict = faceZoneDict[i]->Dictionary();
    vtkFoamEntry *faceLabelsEntry = dict.Lookup("faceLabels");
    if (faceLabelsEntry == NULL)
      {
      delete faceZoneDictPtr;
      vtkErrorMacro(<<"faceLabels not found in faceZones");
      return false;
      }


    if (faceLabelsEntry->FirstValue().GetType() == vtkFoamToken::EMPTYLIST)
      {
      vtkPolyData *fzm = vtkPolyData::New();
      faceZoneMesh->SetBlock(i, fzm);
      fzm->Delete();

      this->SetBlockName(faceZoneMesh, i, faceZoneDict[i]->GetKeyword().c_str());
      continue;
      }

    if (faceLabelsEntry->FirstValue().GetType() != vtkFoamToken::LABELLIST)
      {
      delete faceZoneDictPtr;
      vtkErrorMacro(<<"faceLabels not of type labelList");
      return false;
      }

    vtkIntArray &labels = faceLabelsEntry->LabelList();

    int nFaces = labels.GetNumberOfTuples();
    if (nFaces > this->FaceOwner->GetNumberOfTuples())
      {
      vtkErrorMacro(<<"The length of faceLabels " << nFaces
          << " for faceZone " << faceZoneDict[i]->GetKeyword().c_str()
          << " exceeds the number of faces "
          << this->FaceOwner->GetNumberOfTuples());
      delete faceZoneDictPtr;
      return false;
      }


    vtkPolyData *fzm = vtkPolyData::New();


    fzm->Allocate(nFaces);


    int maxNFacePoints = 0;
    for (int j = 0; j < nFaces; j++)
      {
      const int nFacePoints = facesPoints->GetSize(labels.GetValue(j));
      if (nFacePoints > maxNFacePoints)
        {
        maxNFacePoints = nFacePoints;
        }
      }
    vtkIdList *facePointsVtkId = vtkIdList::New();
    facePointsVtkId->SetNumberOfIds(maxNFacePoints);


    this->InsertFacesToGrid(fzm, facesPoints, 0, nFaces, NULL, facePointsVtkId,
        &labels, false);

    facePointsVtkId->Delete();
    fzm->SetPoints(points);
    faceZoneMesh->SetBlock(i, fzm);
    fzm->Delete();

    this->SetBlockName(faceZoneMesh, i, faceZoneDict[i]->GetKeyword().c_str());
    }

  delete faceZoneDictPtr;

  return true;
}
