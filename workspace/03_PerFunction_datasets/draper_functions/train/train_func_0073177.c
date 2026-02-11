SmoothingVertex(int nbiter,Real8 omega )
  {

    if (quadtree) delete quadtree;
    quadtree=0;
    ReMakeTriangleContainingTheVertex();
    Triangle vide;
    Triangle   ** tstart= new Triangle* [nbv];
    Int4 i,j,k;

    if ( this == & BTh)
     for ( i=0;i<nbv;i++)
      tstart[i]=vertices[i].t;
    else
     for ( i=0;i<nbv;i++)
      tstart[i]=0;
    for ( j=0;j<NbVerticesOnGeomVertex;j++ )
      tstart[ Number(VerticesOnGeomVertex[j].mv)]=&vide;
    for ( k=0;k<NbVerticesOnGeomEdge;k++ )
      tstart[ Number(VerticesOnGeomEdge[k].mv)]=&vide;
    if(verbosity>2)
      cout << "  -- SmoothingVertex: nb Iteration = " << nbiter << " Omega = " << omega << endl;
    for (k=0;k<nbiter;k++)
     {
      Int4 i,NbSwap =0;
      Real8 delta =0;
      for ( i=0;i<nbv;i++)
        if (tstart[i] != &vide)
	  delta=Max(delta,vertices[i].Smoothing(*this,BTh,tstart[i],omega));
      if (!NbOfQuad)
      for ( i=0;i<nbv;i++)
        if (tstart[i] != &vide)
	  NbSwap += vertices[i].Optim(1);
       if (verbosity>3)
	 cout << "    Move max = " <<  sqrt(delta) << " iteration = "
	      << k << " Nb of Swap = " << NbSwap << endl;
       }

    delete [] tstart;
    if (quadtree) quadtree= new QuadTree(this);
  }
