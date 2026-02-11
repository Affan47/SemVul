AddCellToClique( CliqueType & clique,
      vtkIdType a, vtkIdType b, vtkIdType c, vtkIdType d)
    {
    CellType v(4);
    v[0] = a; v[1] = b; v[2] = c; v[3] = d;
    clique.push_back(v);
    }
