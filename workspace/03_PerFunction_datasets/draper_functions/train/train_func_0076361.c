operator>>(istream &sin, vtkQuadratureSchemeDefinition &def)
{


  int cellType, nNodes, nQuadPts;
  sin >> cellType
      >> nNodes
      >> nQuadPts;

  double *SfWt=0,*QWt=0,*pWt=0;
  if ((nNodes>0) && (nQuadPts>0))
    {

    SfWt=new double [nQuadPts*nNodes];
    pWt=SfWt;
    for (int ptId=0; ptId<nQuadPts; ++ptId)
      {
      for (int nodeId=0; nodeId<nNodes; ++nodeId)
        {
        sin >> pWt[0];
        ++pWt;
        }
      }

    QWt=new double [nQuadPts];
    pWt=QWt;
    for (int nodeId=0; nodeId<nNodes; ++nodeId)
      {
      sin >> pWt[0];
      ++pWt;
      }
    }
  else
    {
    vtkGenericWarningMacro("Empty definition found in stream.");
    }


  def.Initialize(cellType,nNodes,nQuadPts,SfWt,QWt);


  if (SfWt!=NULL)
    {
    delete [] SfWt;
    }
  if (QWt!=NULL)
    {
    delete [] QWt;
    }

  return sin;
}
