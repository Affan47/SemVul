ComputeFStats(const ColumnVector& p_fs, int p_dof1, const ColumnVector& p_dof2, ColumnVector& p_zs)
  {
    Tracer_Plus ts("F2z::ComputeFStats");

    int numTS = p_fs.Nrows();

    p_zs.ReSize(numTS);
    F2z& f2z = F2z::getInstance();

    for(int i = 1; i <= numTS; i++)
      {
	if (p_fs(i) > 0.0)
	  {


	    p_zs(i) = f2z.convert(p_fs(i),int(p_dof1),int(p_dof2(i)));
	  }
	else
	  {
	    p_zs(i) = 0.0;
	  }
      }
  }
