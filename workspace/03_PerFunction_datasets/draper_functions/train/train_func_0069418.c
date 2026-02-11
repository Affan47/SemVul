vtkNearestNeighborInterpolation(double point[3],
                                            double displacement[3],
                                            void *gridPtr, int gridType,
                                            int gridExt[6],
                                            vtkIdType gridInc[3])
{
  int gridId[3];
  gridId[0] = vtkInterpolationMath::Round(point[0])-gridExt[0];
  gridId[1] = vtkInterpolationMath::Round(point[1])-gridExt[2];
  gridId[2] = vtkInterpolationMath::Round(point[2])-gridExt[4];

  int ext[3];
  ext[0] = gridExt[1]-gridExt[0];
  ext[1] = gridExt[3]-gridExt[2];
  ext[2] = gridExt[5]-gridExt[4];


  if ((gridId[0] | (ext[0] - gridId[0]) |
       gridId[1] | (ext[1] - gridId[1]) |
       gridId[2] | (ext[2] - gridId[2])) < 0)
    {
    for (int i = 0; i < 3; i++)
      {
      if (gridId[i] < 0)
        {
        gridId[i] = 0;
        }
      else if (gridId[i] > ext[i])
        {
        gridId[i] = ext[i];
        }
      }
    }


  vtkIdType increment = gridId[0]*gridInc[0] +
                        gridId[1]*gridInc[1] +
                        gridId[2]*gridInc[2];

  switch (gridType)
    {
    vtkTemplateMacro(
      vtkNearestHelper(displacement, static_cast<VTK_TT*>(gridPtr), increment));
    }
}
