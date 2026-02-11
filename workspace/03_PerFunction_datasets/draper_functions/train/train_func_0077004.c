GetTiledSizeAndOrigin(int *usize, int *vsize,
                                        int *lowerLeftU, int *lowerLeftV)
{
  double *vport;


  vport = this->GetViewport();


  double tileViewPort[4];
  if (this->GetVTKWindow())
    {
    this->GetVTKWindow()->GetTileViewport(tileViewPort);
    }
  else
    {
    tileViewPort[0] = 0;
    tileViewPort[1] = 0;
    tileViewPort[2] = 1;
    tileViewPort[3] = 1;
    }

  double vpu, vpv;


  vpu = (vport[0] - tileViewPort[0]);
  vpv = (vport[1] - tileViewPort[1]);
  vtkViewportBound(vpu,vpv);

  this->NormalizedDisplayToDisplay(vpu,vpv);
  *lowerLeftU = static_cast<int>(vpu+0.5);
  *lowerLeftV = static_cast<int>(vpv+0.5);
  double vpu2, vpv2;


  vpu2 = (vport[2] - tileViewPort[0]);
  vpv2 = (vport[3] - tileViewPort[1]);
  vtkViewportBound(vpu2,vpv2);

  if (vpu2 > (tileViewPort[2] - tileViewPort[0]))
    {
    vpu2 = tileViewPort[2] - tileViewPort[0];
    }
  if (vpv2 > (tileViewPort[3] - tileViewPort[1]))
    {
    vpv2 = tileViewPort[3] - tileViewPort[1];
    }
  this->NormalizedDisplayToDisplay(vpu2,vpv2);


  *usize = static_cast<int>(vpu2 + 0.5) - *lowerLeftU;
  *vsize = static_cast<int>(vpv2 + 0.5) - *lowerLeftV;
  if (*usize < 0)
    {
    *usize = 0;
    }
  if (*vsize < 0)
    {
    *vsize = 0;
    }
}
