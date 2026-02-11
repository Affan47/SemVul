construct_rotmat_euler(const ColumnVector& params, int n, Matrix& aff)
    {
      Tracer tr("construct_rotmat_euler");
      ColumnVector centre(3);
      centre = 0.0;
      return construct_rotmat_euler(params,n,aff,centre);
    }
