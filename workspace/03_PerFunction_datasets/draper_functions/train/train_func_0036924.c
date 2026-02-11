IntersectWithLine(double* p1, double* p2,
                                           double tol, double& t,
                                           double* x, double* pcoords, int& subId)
{
  int intersection=0;
  double tTemp;
  double pc[3], xTemp[3];
  int faceNum;
  int inter;

  t = VTK_DOUBLE_MAX;
  for (faceNum=0; faceNum<5; faceNum++)
    {


    if(faceNum > 0)
      {
      for (int i=0; i<6; i++)
        {
        this->TriangleFace->PointIds->SetId(i,
              this->PointIds->GetId(PyramidFaces[faceNum][i]));
        }
      inter = this->TriangleFace->IntersectWithLine(p1, p2, tol, tTemp,
                                                    xTemp, pc, subId);
      }
    else
      {
      for (int i=0; i<8; i++)
        {
        this->Face->Points->SetPoint(i,
              this->Points->GetPoint(PyramidFaces[faceNum][i]));
        }
      inter = this->Face->IntersectWithLine(p1, p2, tol, tTemp,
                                            xTemp, pc, subId);
      }
    if ( inter )
      {
      intersection = 1;
      if ( tTemp < t )
        {
        t = tTemp;
        x[0] = xTemp[0]; x[1] = xTemp[1]; x[2] = xTemp[2];
        switch (faceNum)
          {
          case 0:
            pcoords[0] = 0.0; pcoords[1] = pc[1]; pcoords[2] = pc[0];
            break;

          case 1:
            pcoords[0] = 1.0; pcoords[1] = pc[0]; pcoords[2] = pc[1];
            break;

          case 2:
            pcoords[0] = pc[0]; pcoords[1] = 0.0; pcoords[2] = pc[1];
            break;

          case 3:
            pcoords[0] = pc[1]; pcoords[1] = 1.0; pcoords[2] = pc[0];
            break;

          case 4:
            pcoords[0] = pc[1]; pcoords[1] = pc[0]; pcoords[2] = 0.0;
            break;

          case 5:
            pcoords[0] = pc[0]; pcoords[1] = pc[1]; pcoords[2] = 1.0;
            break;
          }
        }
      }
    }
  return intersection;
}
