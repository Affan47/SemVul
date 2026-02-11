GetDolfinCellFaceOrder(vtkCell* cell, vtkIdList *dolfinFaceOrder)
{
  dolfinFaceOrder->Initialize();

  int cellType = cell->GetCellType();

  vtkIdList* dolfinConnectivity = vtkIdList::New();
  GetDolfinCellConnectivity(cell,dolfinConnectivity);
  vtkIdList* inverseDolfinConnectivity = vtkIdList::New();
  inverseDolfinConnectivity->SetNumberOfIds(dolfinConnectivity->GetNumberOfIds());
  for (int i=0; i<dolfinConnectivity->GetNumberOfIds(); i++)
    {
    inverseDolfinConnectivity->SetId(dolfinConnectivity->GetId(i),i);
    }


  switch(cellType)
    {
    case VTK_TETRA:
      dolfinFaceOrder->SetNumberOfIds(4);
      for (int i=0; i<4; i++)
        {
        int* faceArray = vtkTetra::GetFaceArray(i);
        for (int j=0; j<4;j++)
          {
          bool inFaceArray = false;
          for (int k=0;k<3;k++)
            {
            if (inverseDolfinConnectivity->GetId(faceArray[k])==j)
              {
                inFaceArray = true;
              }
            }
          if (!inFaceArray)
            {
            dolfinFaceOrder->SetId(i,j);
            break;
            }
          }
        }
      break;
    default:
      cerr<<"Element type not currently supported in dolfin. Skipping element for face ordering."<<endl;
      break;
    }

  dolfinConnectivity->Delete();
}
