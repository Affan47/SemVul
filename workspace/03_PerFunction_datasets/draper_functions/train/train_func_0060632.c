Setup(OBMol &mol,OBMol &box,double cutoff,double res)
  {
    this->Init(box);

    _inc = res;

    _nxinc = (int) floor((_xmax - _xmin)/0.5);
    _nyinc = (int) floor((_ymax - _ymin)/0.5);
    _nzinc = (int) floor((_zmax - _zmin)/0.5);
    _maxinc = _nxinc*_nyinc*_nzinc;

    int j,size = _nxinc*_nyinc*_nzinc;
    cell.resize(size);
    for (unsigned int num = 0; num < cell.size(); ++num)
      cell[num].resize(0);

    cutoff *= cutoff;

    int k,l,m;
    double x,y,z,dx_2,dy_2;
    double *c = mol.GetCoordinates();
    size = mol.NumAtoms()*3;

    OBAtom *atom;
    vector<OBAtom*>::iterator i;
    for (atom = mol.BeginAtom(i),j=0;atom;atom = mol.NextAtom(i),j+=3)
      if (PointIsInBox(c[j],c[j+1],c[j+2]))
        for (x = _xmin+(_inc/2.0),k=0;k < _nxinc;x+=_inc,++k)
          if ((dx_2 = SQUARE(c[j]-x)) < cutoff)
            for (y = _ymin+(_inc/2.0),l=0;l < _nyinc;y+=_inc,++l)
              if ((dx_2+(dy_2 = SQUARE(c[j+1]-y))) < cutoff)
                for (z = _zmin+(_inc/2.0),m=0;m < _nzinc;z+=_inc,++m)
                  if ((dx_2+dy_2+SQUARE(c[j+2]-z)) < cutoff)
                    cell[(k*_nyinc*_nzinc)+(l*_nzinc)+m].push_back(atom->GetIdx());

    _inc = 1/_inc;
  }
