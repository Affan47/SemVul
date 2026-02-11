MakeTractIdsAdjacent(vtkPolyData* centerlineTracts)
{
  vtkIntArray* centerlineIdsArray = vtkIntArray::SafeDownCast(centerlineTracts->GetCellData()->GetArray(this->CenterlineIdsArrayName));
  vtkIntArray* tractIdsArray = vtkIntArray::SafeDownCast(centerlineTracts->GetCellData()->GetArray(this->TractIdsArrayName));

  vtkIdList* centerlineIds = vtkIdList::New();
  for (int i=0; i<centerlineIdsArray->GetNumberOfTuples(); i++)
    {
    int centerlineId = centerlineIdsArray->GetValue(i);
    centerlineIds->InsertUniqueId(centerlineId);
    }

  for (int i=0; i<centerlineIds->GetNumberOfIds(); i++)
    {
    int centerlineId = centerlineIds->GetId(i);
    vtkIdList* tractIdsMap = vtkIdList::New();
    int maxTractId = -1;
    for (int j=0; j<tractIdsArray->GetNumberOfTuples(); j++)
      {
      if (centerlineIdsArray->GetValue(j) != centerlineId)
        {
        continue;
        }
      int tractId = tractIdsArray->GetValue(j);
      if (tractId > maxTractId)
        {
        maxTractId = tractId;
        }
      }
    tractIdsMap->SetNumberOfIds(maxTractId+1);
    for (int j=0; j<tractIdsMap->GetNumberOfIds(); j++)
      {
      tractIdsMap->SetId(j,0);
      }
    for (int j=0; j<tractIdsArray->GetNumberOfTuples(); j++)
      {
      if (centerlineIdsArray->GetValue(j) != centerlineId)
        {
        continue;
        }
      int tractId = tractIdsArray->GetValue(j);
      tractIdsMap->SetId(tractId,1);
      }
    int currentTractId = 0;
    for (int j=0; j<tractIdsMap->GetNumberOfIds(); j++)
      {
      if (tractIdsMap->GetId(j) == 0)
        {
        continue;
        }
      tractIdsMap->SetId(j,currentTractId);
      currentTractId += 1;
      }
    for (int j=0; j<tractIdsArray->GetNumberOfTuples(); j++)
      {
      if (centerlineIdsArray->GetValue(j) != centerlineId)
        {
        continue;
        }
      int tractId = tractIdsArray->GetValue(j);
      tractIdsArray->SetValue(j,tractIdsMap->GetId(tractId));
      }
    tractIdsMap->Delete();
    }
  centerlineIds->Delete();
}
