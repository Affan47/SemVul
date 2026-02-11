PyramidToTetra(const vtkIdType *pyramId,
                                        const vtkIdType *cellIds,
                                        vtkCellArray *newCellArray)
{
  vtkIdType xmin;
  unsigned int i,j,idpy;
  vtkIdType tab[4];


  const vtkIdType vpy[8][4] ={{0,1,2,4},{0,2,3,4},{1,2,3,4},{1,3,0,4},
                              {2,3,0,4},{2,0,1,4},{3,0,1,4},{3,1,2,4}};

  xmin = cellIds[pyramId[0]];
  idpy = 0;
  for(i=1;i<4;i++)
    {
    if(xmin > cellIds[pyramId[i]])
      {
      xmin = cellIds[pyramId[i]];
      idpy = i;
      }
    }
  for(j = 0; j < 4 ; j++)
    {
    tab[j] = pyramId[vpy[2*idpy][j]];
    }
  newCellArray->InsertNextCell(4,tab);

  for(j = 0; j < 4 ; j++)
    {
    tab[j] = pyramId[vpy[2*idpy+1][j]];
    }
  newCellArray->InsertNextCell(4,tab);
}
