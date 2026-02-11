SetDihedralAtoms(int ref[4])
  {

    _ref.resize(4);
    for (int i = 0;i < 4;++i)
      _ref[i] = ref[i];
    _torsion.resize(4);

    _torsion[0] = (ref[0]-1)*3;
    _torsion[1] = (ref[1]-1)*3;
    _torsion[2] = (ref[2]-1)*3;
    _torsion[3] = (ref[3]-1)*3;
  }
