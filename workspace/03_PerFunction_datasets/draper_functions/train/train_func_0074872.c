transpose(SparseMatrix& ret)
  {
    Tracer_Plus tr("SparseMatrix::transpose");

    ret.ReSize(ncols,nrows);

    for(int r=1; r <= nrows; r++)
      for(map<int,double>::const_iterator it=data[r-1].begin(); it!=data[r-1].end(); it++)
	ret.insert((*it).first+1, r, (*it).second);

  }
